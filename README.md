# Hand Gesture Controlled Car

### This project uses a hand gesture recognition system to control a car wirelessly via a Bluetooth module. The project employs an MPU6050 sensor to detect hand gestures and transmits commands via Bluetooth to a microcontroller that controls the car's motors.

## Project Structure

### - motor.ino: This file contains the code that controls the car's motors based on commands received via Bluetooth.

### - hand.ino: This file contains the code for recognizing hand gestures using the MPU6050 sensor and sending appropriate commands via Bluetooth.

## Features

### - hand.ino: This file contains the code for recognizing hand gestures using the MPU6050 sensor and sending appropriate commands via Bluetooth.

### - Bluetooth Communication: The hand gesture system communicates with the car controller via Bluetooth.

### - Motor Control: The car has four DC motors that are independently controlled to provide directional movement.

## Components Used

### - MPU6050 Accelerometer/Gyroscope
### - AFMotor Shield for Arduino
### - Bluetooth Module (HC-05/06)
### - Arduino Microcontroller
### - DC Motors

## Command Descriptions

### - FORWARD ('F'): Move forward.
### - BACKWARD ('B'): Move backward.
### - LEFT ('L'): Turn left.
### - RIGHT ('R'): Turn right.
### - STOP ('S'): Stop the car.

