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

//#define OV2640_I2C_ADDR 0x60  // 0x30 << 1


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

void OV2640Camera::printCaptureReport(UART_HandleTypeDef* huart) {
    char buf[128];

    // --- Sample Pixels ---
    HAL_UART_Transmit(huart, (uint8_t*)"\r\n--- Pixel Samples ---\r\n", 25, HAL_MAX_DELAY);
    for (int i = 0; i < 32; i += 2) {
        uint16_t pixel = (frame_buffer_[i] << 8) | frame_buffer_[i + 1];
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        uint8_t r8 = (r * 255) / 31;
        uint8_t g8 = (g * 255) / 63;
        uint8_t b8 = (b * 255) / 31;
        snprintf(buf, sizeof(buf), "Pixel %03d: R=%3u G=%3u B=%3u\r\n", i / 2, r8, g8, b8);
        HAL_UART_Transmit(huart, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
    }

    // --- Average Color ---
    size_t red = 0, green = 0, blue = 0;
    size_t samples = 0;
    const size_t step = 2;

    for (size_t i = 0; i + 1 < FRAME_SIZE; i += step) {
        uint16_t pixel = (frame_buffer_[i] << 8) | frame_buffer_[i + 1];
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        red += r;
        green += g;
        blue += b;
        samples++;
    }

    uint8_t avgR = (red * 255 / 31) / samples;
    uint8_t avgG = (green * 255 / 63) / samples;
    uint8_t avgB = (blue * 255 / 31) / samples;

    HAL_UART_Transmit(huart, (uint8_t*)"\r\n--- Frame Summary ---\r\n", 25, HAL_MAX_DELAY);
    snprintf(buf, sizeof(buf), "Avg RGB: R=%u G=%u B=%u\r\n", avgR, avgG, avgB);
    HAL_UART_Transmit(huart, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);

    // --- Dominant Color ---
    DominantColor dom = analyzeColor();
    const char* colorStr = "UNKNOWN";
    if (dom == COLOR_RED) colorStr = "RED";
    else if (dom == COLOR_GREEN) colorStr = "GREEN";
    else if (dom == COLOR_BLUE) colorStr = "BLUE";

    snprintf(buf, sizeof(buf), "Dominant Color: %s\r\n", colorStr);
    HAL_UART_Transmit(huart, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
}

DominantColor OV2640Camera::analyzeColor() {
    size_t red = 0, green = 0, blue = 0;
    const size_t step = 2;
    size_t samples = 0;

    for (size_t i = 0; i + 1 < FRAME_SIZE; i += step) {
        uint16_t pixel = (frame_buffer_[i] << 8) | frame_buffer_[i + 1];
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        red += r;
        green += g;
        blue += b;
        samples++;
    }

    // Normalize to average
    red /= samples;
    green /= samples;
    blue /= samples;

    // Brightness threshold
    if ((red + green + blue) < 30) return COLOR_UNKNOWN;

    // Color dominance margin
    if ((red > green + 5) && (red > blue + 5)) return COLOR_RED;
    if ((green > red + 5) && (green > blue + 5)) return COLOR_GREEN;
    if ((blue > red + 5) && (blue > green + 5)) return COLOR_BLUE;

    return COLOR_UNKNOWN;
}


DominantColor OV2640Camera::analyzeColorCenter() {
    size_t red = 0, green = 0, blue = 0;
    size_t samples = 0;

    // Define center region (central 25%)
    const int x_start = 60;
    const int x_end   = 100;
    const int y_start = 45;
    const int y_end   = 75;

    for (int y = y_start; y < y_end; y++) {
        for (int x = x_start; x < x_end; x++) {
            size_t index = (y * 160 + x) * 2;
            uint16_t pixel = (frame_buffer_[index] << 8) | frame_buffer_[index + 1];
            uint8_t r = (pixel >> 11) & 0x1F;
            uint8_t g = (pixel >> 5) & 0x3F;
            uint8_t b = pixel & 0x1F;

            red += r;
            green += g;
            blue += b;
            samples++;
        }
    }

    // Compute average
    red /= samples;
    green /= samples;
    blue /= samples;

    // Optional brightness check
    if ((red + green + blue) < 30) return COLOR_UNKNOWN;

    // Use margin threshold to declare a winner
    if ((red > green + 5) && (red > blue + 5)) return COLOR_RED;
    if ((green > red + 5) && (green > blue + 5)) return COLOR_GREEN;
    if ((blue > red + 5) && (blue > green + 5)) return COLOR_BLUE;

    return COLOR_UNKNOWN;
}

void OV2640Camera::printBlueDetectionMap(UART_HandleTypeDef* huart) {
    const size_t width = 160;
    const size_t height = 120;
    const size_t stride = 2;  // each pixel is 2 bytes

    char rowBuffer[SAMPLE_WIDTH + 3];  // + newline and \0
    size_t pixelIndex = 0;

    for (size_t y = 0; y < height; y += 2) {  // skip every other row for speed
        size_t rowPos = 0;

        for (size_t x = 0; x < width * stride; x += STEP * stride) {
            uint16_t i = y * width * stride + x;
            if (i + 1 >= FRAME_SIZE) break;

            uint16_t pixel = (frame_buffer_[i] << 8) | frame_buffer_[i + 1];
            uint8_t r5 = (pixel >> 11) & 0x1F;
            uint8_t g6 = (pixel >> 5) & 0x3F;
            uint8_t b5 = pixel & 0x1F;

            uint8_t b8 = (b5 * 255) / 31;

            // Binary classification: is this "blue" enough?
            if (b8 >= BLUE_THRESHOLD) {
                rowBuffer[rowPos++] = 'b';
            } else {
                rowBuffer[rowPos++] = '_';
            }
        }

        rowBuffer[rowPos++] = '\r';
        rowBuffer[rowPos++] = '\n';
        rowBuffer[rowPos] = '\0';

        HAL_UART_Transmit(huart, (uint8_t*)rowBuffer, strlen(rowBuffer), HAL_MAX_DELAY);
    }
}

