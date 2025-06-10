/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : camera.cpp
  * @brief          : File containing the Functions to the OV2640 (Camera)
  * @author			: Arath Villanueva (abvillan@calpoly.edu) Devon Bolt (dwbolt@calpoly.edu)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "camera.h"
#include "cameraRegs.h"
#include <cstring> // for memset

OV2640Camera::OV2640Camera(I2C_HandleTypeDef* i2c, SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin)
    : i2c_(i2c), spi_(spi), cs_port_(cs_port), cs_pin_(cs_pin) {
    memset(frame_buffer_, 0, FRAME_SIZE);
}

void OV2640Camera::csHigh() {
    HAL_GPIO_WritePin(cs_port_, cs_pin_, GPIO_PIN_SET);
}

void OV2640Camera::csLow() {
    HAL_GPIO_WritePin(cs_port_, cs_pin_, GPIO_PIN_RESET);
}

void OV2640Camera::writeRegister(uint8_t reg, uint8_t val) {
    HAL_I2C_Mem_Write(i2c_, 0x60, reg, I2C_MEMADD_SIZE_8BIT, &val, 1, HAL_MAX_DELAY);
}

bool OV2640Camera::initialize() {
    const regval_list* reg = OV2640_RGB565_QQVGA;
    while (!(reg->reg == 0xFF && reg->val == 0xFF)) {
        writeRegister(reg->reg, reg->val);
        HAL_Delay(2);
        reg++;
    }
    return true;
}

bool OV2640Camera::captureFrame() {
    // Clear FIFO
    csLow();
    uint8_t cmd = 0x04; // FIFO_CLEAR
    HAL_SPI_Transmit(spi_, &cmd, 1, HAL_MAX_DELAY);
    csHigh();

    HAL_Delay(2);

    // Start capture
    csLow();
    cmd = 0x02; // START_CAPTURE
    HAL_SPI_Transmit(spi_, &cmd, 1, HAL_MAX_DELAY);
    csHigh();

    HAL_Delay(100); // crude wait; polling FIFO_DONE bit is ideal

    // Read frame from FIFO
    csLow();
    cmd = 0x3C; // READ_FIFO
    HAL_SPI_Transmit(spi_, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(spi_, frame_buffer_, FRAME_SIZE, HAL_MAX_DELAY);
    csHigh();

    return true;
}

DominantColor OV2640Camera::analyzeColor() {
    size_t red = 0, green = 0, blue = 0;
    const size_t step = 4; // Sample every 2nd pixel (speed up)

    for (size_t i = 0; i + 1 < FRAME_SIZE; i += step) {
        uint16_t pixel = (frame_buffer_[i] << 8) | frame_buffer_[i + 1];

        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        red += r;
        green += g;
        blue += b;
    }

    if (red > green && red > blue) return COLOR_RED;
    if (green > red && green > blue) return COLOR_GREEN;
    if (blue > red && blue > green) return COLOR_BLUE;
    return COLOR_UNKNOWN;
}
