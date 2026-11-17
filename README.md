# Real-Time Sensor Monitoring Station Using Periodic Task Scheduler

## Project Overview
This project monitors multiple sensors using the LPC2129 ARM7 microcontroller. A periodic task scheduler based on Timer1 interrupts performs sensor readings at predefined intervals and sends the results through UART communication.

## Hardware Requirements
- LPC2129 ARM7 Microcontroller
- LM35 Temperature Sensor
- Potentiometer
- LDR Sensor
- Flame Sensor
- Vibration Sensor
- LED
- UART-to-USB Converter

## Software Requirements
- Keil µVision 5
- Embedded C
- Serial Terminal

## Features
- Real-time temperature monitoring
- Potentiometer voltage monitoring
- Light intensity monitoring
- Flame detection
- Vibration detection
- UART serial communication
- Timer1-based periodic task scheduling

## Project Files
| File | Description |
|---|---|
| main.c | Main program and sensor monitoring |
| uart.c | UART communication functions |
| adc.c | ADC initialization and sensor readings |
| timer1.c | Timer1 interrupt and task scheduler |
| header.h | Header file and function declarations |

## Working Principle
1. Initialize UART, ADC, GPIO and Timer1.
2. Timer1 generates periodic interrupts.
3. The interrupt sets task flags at predefined intervals.
4. The main program checks these flags and reads the corresponding sensors.
5. Sensor values and detection status are transmitted through UART.

## Applications
- Environmental monitoring
- Industrial safety systems
- Embedded monitoring applications

## Author
Shaik Umar Farooq
