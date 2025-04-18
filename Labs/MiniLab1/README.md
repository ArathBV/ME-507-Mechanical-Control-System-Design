# ME 507 MiniLab#1 Pulse a LED
### Lab Takeaways
- The purpose of the lab was to familiarize ourselves with using the crystal oscillator on the Blackpill development board rather than using the RCC timers and software delays in order to create a pulse of 500ms to blink an LED. The setup of the lab follows the same setup as the previous lab with RCC timers. The noticable differences between using the crystal oscillator was that it was far more accurate compared to using the RCC timers and software delays and this is due to the oscillator being able to stabilize high frequencies generated by the clock which eliminates possibilites of noise. During this lab we also used a timer interrupt in order to count the amount of pulses that the LED/ PWM waveform had completed a period. Through this interrupt we were able to print out the current duty cycle of the signal and the LED blink status. 
### Oscilloscope Reading
![ME507Lab2P2](https://github.com/user-attachments/assets/22771b83-68fd-46f5-a788-b19ba3439887)
### Terminal Output
![ME507Lab2P1](https://github.com/user-attachments/assets/381877a2-715a-443d-8eab-01e3ccc4502a)
