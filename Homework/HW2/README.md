# Homework 2: Minimal MCU Design
**Arath Villanueva**\
**20, April 2025**
- The PCB design implements the custom MCU package created in Homework 1. The PCB consists of an input of 12.6 to 11.1 V from a 3 cell LiPo Battery. This is then safeguarded by two switches and a fuse to avoid battery damage. This is then followed by an ADC to check the status of the battery life and LED to indicate the board is being powered properly. The original voltage from the LiPo battery is then stepped down by a buck converter to 5V and followed by another voltage regulator to 3.3V. The STM32F411 64 pin package contains two crystal oscillators, an ST-Link for SWD communication for flashing and debugging software on the MCU, and decoupling capacitors for each Vdd and Vref input for the MCU. The routing of the PCB and components is on a 4 layer PCB containing 2 ground planes for heat dispersion of components and the heat generated by the input voltage.
## Schematic
![SchematicLayoutHW3](https://github.com/user-attachments/assets/1eb5e97f-0fcf-4988-b66f-a0382a9a8f06)
  ### MCU
  ![SchematicMCUHW3](https://github.com/user-attachments/assets/6514900c-9dc9-4431-aebc-d1b2e33813ac)
  ### MCU Oscillators
  ![SchematicMCUOscHW3](https://github.com/user-attachments/assets/f1a76d2d-28fa-4dc9-ab72-b24f7ad9d8d5)
  ### Power Regulator
  ![SchematicPowerRegHW3](https://github.com/user-attachments/assets/3d1cbebb-a807-4904-a14c-6f1d08d0b6a1)
  ### LEDs, ST-Link, Decoupling Caps
  ![SchematicLEDLINKCAPHW3](https://github.com/user-attachments/assets/807790ad-f2a8-4d21-94e8-c2bfba6b1e41)
## PCB Layout
![MCUpcbHW3](https://github.com/user-attachments/assets/75a09d86-af7a-4070-a2ad-af6a336d6487)
## CAD Design
![MCUisoHW3](https://github.com/user-attachments/assets/5f0bbc2f-8aed-4246-8c5d-8c488439521e)
