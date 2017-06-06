# PSI3441-FRDM

## Description

Freescale CodeWarrior 10.7 project for the FRDM-FL25Z. This project models the operation of a PMSM driver through some MCU navel-gazing.

In a nutshell, the MCU's DAC generates a 60 Hz sine wave, which is then sampled by the ADC (a jumper wire is required for this connection). After some signal processing, which may include FIR filters and phase shifters, the processed sine wave is then passed to a timer's Output Compare module to emulate a half-bridge driver.


## Architecture

### Overview


### DAC

At this time, the DAC is driving a sine wave from memory with the help of the DMA's Channel 0 in Always Enabled mode with periodic PIT triggering.

The `DMACH1_OnComplete` ISR restarts the DMA channel after a large number of transfers (it cannot be kept on indefinitely).


### ADC

At this time, the hardware-triggered ADC is filling a buffer in memory through interrupt servicing.


### Signal processing


### Output compare
