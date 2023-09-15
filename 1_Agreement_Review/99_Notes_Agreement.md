# BÜP Project S5
Time: 34 lessons

Develop a tiny extension Board for the STM32H747i-Disco Board, to allow it to act as a DMM. 
Additionally a software, that measures the DMM Values and displays them on the Touch Display.
If there's more time i could extend the Project with Measurement Logging via a SD-Card or over USB to a Desktop application.

## Hardware Requirements
- Connect to the STM32H747I-Disco Board.
- Not the final Product, so no galvanic separation.
	- Measure Analog Voltages and Currents.
	- Measure the Values of Resistors and Capacitors.
	- Adressable LEDs that show when a Connection is shorted.

## Software Requirements
- drive the SDRAM, so its used as a main ram.
- drive the QSPI Flash, so the code is on it and the MCU boots from the external QSPI Flash.

## Things to learn
- QSPI
- Bootloaders
- FreeRTOS
- C++
- TouchGFX
- FAT
- SD-Card

## Things i already know (Won't be documented)
- ADC with DMA
- Adressable LEDs


# Softskills
- Documentation in English and LaTex
- Version management in Git with 