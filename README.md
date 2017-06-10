# PSI3441-FRDM

## Summary

Freescale CodeWarrior 10.7 project for the FRDM-FL25Z. This project models the operation of a three-phase PMSM driver with back-EMF sensing through some MCU navel-gazing.

In a nutshell, the MCU's DAC generates a 60 Hz sine wave, which is then sampled by the ADC (a jumper wire is required for this connection). After some signal processing, which may include FIR filters and [adjustable] phase shifters, the processed sine wave is passed to a timer for PWM generation.


## Description

### Overview


### DAC

At this time, the DAC is driving a sine wave from memory with the help of the DMA's channel 1 triggered by the TPM1 overflow. Currently, the wave period is around 2.1 s.

The `DMA1_IRQHandler` ISR restarts the DMA channel after a large number of transfers (since it cannot be kept on indefinitely).

**Note:** As described in the KL25Z's Errata 5746, the DMA cycle-steal periodic (PIT) trigger operation is faulty. The TPM triggering described above is the recommended workaround.


### ADC

At this time, the TPM2-triggered ADC is filling a buffer in memory through interrupt servicing. For modularity reasons, even though ADC and DAC frequencies can be identical, different timers are used for triggering. This can later be changed if necessary, as using different timers could arguably generate race conditions.


### Signal processing

At this time, the signal processing consists in discarding the LSBs of the ADC to fit the PWM 10-bits output resolution.

A compromise will have to be reached here between the sawtooth carrier frequency and the output resolution.


### PWM

At this time, the TPM0 is generating an ADC-generated DMA-driven variable duty-cycle center-aligned PWM wave slow enough to be seen on the blue LED. The duty cycle is updated with the same frequency, and from the same timer, as the ADC conversion.

**Note:** The `Init_TPM` component, which is the only one that supports center-aligned PWM mode, is buggy. Make sure to call the `TPM0_FixPWM` method.


### Figure of merit

An additional pin will, in time, be used to output the processor load state: whenever the processor enters an ISR or leaves its idle loop, the blue LED is set. Measuring the pin's duty cycle with the help of an oscilloscope provides a simple, yet effective, figure of merit.


## Setup

### Build instructions

Import and build project with CodeWarrior 10.7 or higher.


### Hardware setup

The DAC output is available on pin 11 of connector J10. The blue LED (active LOW) is available on pin 12 of connector J2. The ADC input is available on pin 2 of connector J10.

In order for the system to work, the DAC output must be linked to the ADC input with the help of a jumper wire. The DAC output can otherwise be visualized by connecting it to the blue LED pin. Take care to redirect PWM output in this case, as it is currently routed to the blue LED.


## References

D. Kastha, D. Prasad, N. K. De, S. Sengupta. Lesson 37: Sine PWM and its Realization. *Power Electronics (Web Course): Lecture Notes*. Indian Institute of Technology Kharagpur. http://nptel.ac.in/downloads/108105066/ (2017-06-07).
