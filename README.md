# PSI3441-FRDM

## Summary

Freescale CodeWarrior 10.7 project for the FRDM-FL25Z. This project models the operation of a three-phase PMSM driver with back-EMF sensing through some MCU navel-gazing.

In a nutshell, the MCU's DAC generates a 60 Hz sine wave, which is then sampled by the ADC (a jumper wire is required for this connection). After some signal processing, which may include FIR filters and [adjustable] phase shifters, the processed sine wave is passed to a timer for PWM generation.


## Description

### Overview


### DAC

At this time, the DAC is driving a sine wave from memory with the help of the DMA's Channel 0 in Always Enabled mode with periodic PIT triggering. Currently, this wave is slow enough to be seen on the blue LED.

The `DMACH1_OnComplete` ISR restarts the DMA channel after a large number of transfers (it cannot be kept on indefinitely).

**Note:** Stopping the processor in debug mode for too long may cause it to miss the DMA's ISR and generate a configuration error, for some reason.


### ADC

At this time, the hardware-triggered ADC is filling a buffer in memory through interrupt servicing.


### Signal processing


### PWM

At this time, the TPM2 timer is generating a DMA-driven variable duty-cycle center-aligned PWM wave slow enough to be seen on the red LED.

A compromise will have to be reached here between the sawtooth carrier frequency and the output resolution.

**Note:** The `Init_TPM` component, which is the only one that supports center-aligned PWM mode, is buggy. Make sure to call `TPM2_FixPWM` method.


### Figure of merit

The blue LED will, in time, be used to output the processor load state: whenever the processor enters an ISR or leaves its idle loop, the blue LED is set. Measuring the pin's duty cycle with the help of an oscilloscope provides a simple, yet effective, figure of merit.


## Setup

### Build instructions

Import and build project with CodeWarrior 10.7 or higher.


### Hardware setup

The DAC's output is available on pin 12 of connector J2.

The blue LED (active LOW) is available on pin 11 of connector J10.


## References

D. Kastha, D. Prasad, N. K. De, S. Sengupta. Lesson 37: Sine PWM and its Realization. *Power Electronics (Web Course): Lecture Notes*. Indian Institute of Technology Kharagpur. http://nptel.ac.in/downloads/108105066/ (2017-06-07).
