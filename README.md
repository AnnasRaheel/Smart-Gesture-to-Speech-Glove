# Smart Gesture to Speech Glove

A wearable assistive technology project that converts predefined hand gestures into text and speech using flex sensors, MPU6050 motion sensing, Arduino Mega 2560, HC-05 Bluetooth, and an Android application.

## Project Overview

The Smart Gesture to Speech Glove is designed to assist speech-impaired individuals by providing an affordable and portable communication solution.

The glove detects finger bending and hand orientation using flex sensors and the MPU6050 motion sensor. The Arduino Mega processes the sensor readings and identifies predefined gestures. The corresponding message is then transmitted wirelessly through the HC-05 Bluetooth module to an Android application, where the text can be converted into speech.

## Key Features

- Predefined gesture recognition
- Flex sensor-based finger detection
- MPU6050-based hand orientation detection
- Wireless Bluetooth communication
- Real-time message transmission
- Android application integration
- Portable wearable design
- Low-cost assistive technology approach
- Multiple predefined gesture messages

## Hardware Components

- Arduino Mega 2560
- Flex Sensors (4)
- MPU6050 IMU
- HC-05 Bluetooth Module
- Smart Glove
- Jumper Wires
- Power Supply

## Software

- Arduino IDE
- C/C++ for Arduino
- Android Application
- MPU6050 Library
- Wire Library

## Working Principle

The system works in the following sequence:

1. Flex sensors detect finger bending.
2. The MPU6050 detects hand orientation and motion.
3. Arduino Mega 2560 reads and processes the sensor values.
4. Sensor values are compared with predefined thresholds.
5. A recognized gesture is assigned to a predefined message.
6. The message is transmitted through the HC-05 Bluetooth module.
7. The Android application receives the message and converts the text into speech.

## Flex Sensor Configuration

| Sensor | Finger | Arduino Pin |
|---|---|---|
| F0 | Thumb | A7 |
| F1 | Index | A9 |
| F2 | Middle | A10 |
| F3 | Ring | A11 |

The code uses threshold and release values for detecting finger bending and returning to the neutral position.

## Gesture Detection

The system uses two types of gesture inputs:

### Flex-Based Gestures

Individual and combined finger movements are used to trigger predefined messages.

### MPU6050-Based Gestures

Hand orientation is detected using accelerometer readings along the X and Y axes. Specific orientations are mapped to predefined messages.

## Sensor Smoothing

A moving-average method is used to smooth flex sensor readings.

The program uses a buffer of 6 readings to reduce fluctuations and improve gesture detection stability.

## Communication

The HC-05 Bluetooth module is used to transmit recognized messages wirelessly from the Arduino Mega to the Android application.

The Arduino communicates with the HC-05 through `Serial1` at 9600 baud.

## Project Applications

The system can be used as a prototype for:

- Assistive communication
- Wearable technology research
- Human-computer interaction
- Mechatronics projects
- Gesture-based interfaces
- Communication assistance for speech-impaired individuals

## Future Scope

Possible future improvements include:

- AI and Machine Learning-based gesture recognition
- Larger gesture vocabulary
- Multi-language support
- Improved mobile application features
- IoT and cloud connectivity
- More advanced motion recognition
- Improved sensor calibration and accuracy


## Repository

This repository contains the Arduino source code used for the Smart Gesture to Speech Glove prototype.

### Main File

`Smart_Gesture_to_Speech_Glove.ino`

## Project Status

Prototype completed and demonstrated as a final-year Mechatronics Engineering project.

---

**Smart Communication. Intelligent Translation. Complete Accessibility.**

