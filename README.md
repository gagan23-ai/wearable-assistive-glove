# Wearable Assistive Glove for Communication

## Overview

The **Wearable Assistive Glove** is an ESP32-based assistive communication prototype designed to help people with **speech difficulties and limited hand movement** communicate through hand gestures.

People who cannot speak may have difficulty expressing their needs, while people affected by paralysis may have limited ability to use conventional communication methods. To address this, we developed a wearable glove that converts **finger bending and hand movements into predefined messages**.

The glove uses **three flex sensors** to detect finger gestures and an **MPU6050 motion sensor** to detect directional hand movements. The ESP32 processes these inputs and sends the corresponding message through Bluetooth.

This provides two communication methods:
- **Finger bending → Message**
- **Hand movement → Message**

The prototype demonstrates how simple wearable sensors can be used to create an accessible communication interface.

---

## Gesture-Based Communication

### Finger Gesture Mode

Three flex sensors detect different finger-bending patterns.

| Gesture | Output Message |
|---|---|
| Flex Sensor 1 bent | Introduction message |
| Flex Sensor 2 bent | "What are you doing?" |
| Flex Sensor 3 bent | "How are you?" |

### Motion Gesture Mode

The MPU6050 detects directional hand movements.

| Movement | Output Message |
|---|---|
| Left | "Please come here." |
| Right | "Please wait for me." |
| Up | "I need help." |
| Down | "Thank you for helping me." |

The recognized message is transmitted wirelessly using the ESP32's built-in Bluetooth.

---

## Hardware

- ESP32 DevKit
- 3 × Flex Sensors
- MPU6050 Motion Sensor
- Resistors
- Breadboard
- Connecting Wires
- Glove
- USB / Power Supply

---

## Software & Technologies

- Arduino IDE
- Embedded C / Arduino C++
- ESP32
- Bluetooth
- I2C Communication
- MPU6050
- Analog Sensor Reading

---

## System Architecture

```text
                HAND GESTURES
                     │
           ┌─────────┴─────────┐
           │                   │
    Finger Bending        Hand Movement
           │                   │
     Flex Sensors            MPU6050
       (3 Sensors)        Motion Sensor
           │                   │
           └─────────┬─────────┘
                     │
                    ESP32
                     │
             Gesture Processing
                     │
                 Bluetooth
                     │
                     ▼
             Predefined Message
