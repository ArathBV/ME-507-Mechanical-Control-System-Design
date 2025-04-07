# ME 507 MiniLab#0 Blinky

### Setup
![UART Blinky Setup | 4032x3024,20%](https://github.com/user-attachments/assets/5756692a-edd9-4df2-a656-6cd99aa9bf29)
 - STM32F411 Blackpill Development board conneted to the ST-LINK Programmer/Debugger via the Serial Wire Debug in order to flash the code to the BlackPill board.
   
### PuTTY Terminal Output
![UART PUTTY OUTPUT](https://github.com/user-attachments/assets/867ca618-48c3-4aea-8ab0-43dadd8e6143)
 - Every sequence the LED blinks on the board will output the number of times the LED has blinked since running the program.

### Oscilloscope Timing Readings
![Oscilloscope Timing Delay Readings](https://github.com/user-attachments/assets/50fb78b0-54c9-4ee9-9983-ceaf9eaafb48)
- Oscilloscope demonstrates the measurements in delay between the LED being set high and low to measure the accuracy of the software delays put in place.

### Takeaways
- From completing lab blinky we are able to see how by simply using software delays there is inaccuracy in the timing when acutally measuring the time between the LED is set from high to low. In this lab we wanted to achieve a cycle of 500ms with 200ms of LED On and 300ms of the LED being Off, however when setting the delay to get the total 500ms cycles with the 200ms there was a 8ms discrepancy and with the 300ms set there was a 22ms discrepancy. The reasoning for the discrepancies were concluded to various reasons such as the transmission and print statements to PuTTY, but the main conclusion is due to the software delay functions are not as reliable as using internal hardware timers and the clocks. One of the other reasons is due to using RCC (RC Clock) is not accurate and not as reliable as the delay and timings may change due to heat factors. 

## Demo
[Blinky and UART Demo](https://youtube.com/shorts/pL8lmw1s8vE?feature=share"@embed")

