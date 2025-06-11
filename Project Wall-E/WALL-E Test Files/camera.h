/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : camera.h
  * @brief          : File containing the initialization class to the OV2640 (Camera)
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
#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "stm32f4xx_hal.h"
#include <cstring>
#include <cstdio>

#define BLUE_THRESHOLD 200   // Adjust based on lighting and distance
#define STEP 4               // Read every 2 bytes = 1 pixel, STEP=4 = every other pixel
#define ROW_WIDTH 160
#define SAMPLE_WIDTH (ROW_WIDTH / 2)  // Because we skip every other pixel

enum DominantColor {
    COLOR_UNKNOWN,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
};

class OV2640Camera {
public:
    OV2640Camera(I2C_HandleTypeDef* i2c, SPI_HandleTypeDef* spi, GPIO_TypeDef* cs_port, uint16_t cs_pin);

    bool initialize();
    bool captureFrame();
    void printCaptureReport(UART_HandleTypeDef* huart);
    void printBlueDetectionMap(UART_HandleTypeDef* huart);
    DominantColor analyzeColor();
    DominantColor analyzeColorCenter();

private:
    I2C_HandleTypeDef* i2c_;
    SPI_HandleTypeDef* spi_;
    GPIO_TypeDef* cs_port_;
    uint16_t cs_pin_;

    static constexpr size_t FRAME_SIZE = 160 * 120 * 2; // QQVGA RGB565
    uint8_t frame_buffer_[FRAME_SIZE];

    void writeRegister(uint8_t reg, uint8_t val);
    void csHigh();
    void csLow();
};



#endif /* INC_CAMERA_H_ */
