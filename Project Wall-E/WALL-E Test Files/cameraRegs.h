/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : cameraRegs.h
  * @brief          : File containing the initialization Registers to the OV2640 (Camera)
  * to begin use and configuring for minimal overhead and direct raw data processing via SPI.
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

#ifndef INC_CAMERAREGS_H_
#define INC_CAMERAREGS_H_

#pragma once

struct regval_list {
    uint8_t reg;
    uint8_t val;
};

const regval_list OV2640_RGB565_QQVGA[] = {
    {0xff, 0x01}, {0x12, 0x80}, // Reset
    {0xff, 0x00}, {0x2c, 0xff}, {0x2e, 0xdf},
    {0xff, 0x01}, {0x3c, 0x32}, {0x11, 0x01},
    {0x09, 0x02}, {0x04, 0x28}, {0x13, 0xe5},
    {0x14, 0x48}, {0x2c, 0x0c}, {0x33, 0x78},
    {0x3a, 0x33}, {0x3b, 0xfb}, {0x3e, 0x00},
    {0x43, 0x11}, {0x16, 0x10}, {0x39, 0x92},
    {0x12, 0x04}, {0x8c, 0x00}, {0x40, 0xd0},
    {0x3a, 0x04}, {0xff, 0x00},
    {0xc0, 0x22}, {0xc1, 0x00}, {0x86, 0x00},
    {0x50, 0x92}, {0x51, 0x80}, {0x52, 0x60},
    {0x53, 0x00}, {0x54, 0x00}, {0x55, 0x00},
    {0x57, 0x00}, {0x5a, 0x28}, {0x5b, 0x1e},
    {0x5c, 0x00}, {0xd3, 0x04},
    {0xff, 0x01}, {0x15, 0x00},
    {0xff, 0xff}
};




#endif /* INC_CAMERAREGS_H_ */
