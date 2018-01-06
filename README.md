# Fall Sensor
Fall detection system based on incremental development model.

> This is the appendix of an Engineering Thesis written for AGH University of Science and Technology in the academic year 2017/18.
Author: Lukasz Marcul.

## Latest Release
[Fall Sensor - Fall Detection & Data Acquisition Mode](https://github.com/Marcullo/fall-sensor/releases/tag/v0.12)

## Purpose

### Abstraction
- project based on incremental development model
- a few releases from which any could be a product
- provide prototype for presentation

### Content
Embedded wearable device including fall sensor with automatic
emergency call/notifier system allowing to process data derived from 
the accident.

## Project development steps

1. Build distributed measurement system for collecting data from
the sensor and process it using PC.
2. Perform ADL (activity daily living) scenario and simulate
accidents.
3. Implement fall detection algorithm.
4. Add emergency system.

### Distributed measurement system

#### Hardware
- NUCLEO-L476RG
- Waveshare IMU 10DoF
- programmer/debugger

#### Hardware connection
- IMU - MCU - PC
- used popular serial communication buses (I2C, UART)

#### Software
- MCU: popular platform/library, e.g. mbed, HAL
- PC: Python/Java/LabVIEW data analyzer

#### Software connection
- set of configuration commands
- data packets

