#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

/**
 * Motor Control Pin Definitions
 */
// Motor A PWM control (speed control)
const uint8_t PWMA = D0;
// Motor A direction control pins
const uint8_t AIN2 = D1;
const uint8_t AIN1 = D2;
// Standby pin (HIGH = motors enabled, LOW = motors disabled)
const uint8_t STBY = D10;
// Motor B direction control pins
const uint8_t BIN1 = D3;
const uint8_t BIN2 = D4;
// Motor B PWM control (speed control)
const uint8_t PWMB = D5;

/**
 * LED Matrix Configuration
 */
// Data input pin for LED matrix
const uint8_t LED_DIN = D7;
// LED matrix dimensions
const uint8_t LED_MATRIX_HEIGHT = 16;
const uint8_t LED_MATRIX_WIDTH = 16;
// Total number of LEDs in the matrix
const uint16_t LED_MATRIX_NUM_LEDS = LED_MATRIX_WIDTH * LED_MATRIX_HEIGHT;
// LED brightness level (0-255, set to ~5% to reduce power consumption)
const uint8_t LED_BRIGHTNESS = 13;

/**
 * Direction Constants
 */
const uint8_t DIRECTION_STOP = 0;     // Stop all motors
const uint8_t DIRECTION_FORWARD = 1;  // Move forward
const uint8_t DIRECTION_BACKWARD = 2; // Move backward
const uint8_t DIRECTION_LEFT = 3;     // Turn left (left motor backward, right motor forward)
const uint8_t DIRECTION_RIGHT = 4;    // Turn right (right motor backward, left motor forward)

/**
 * Motor Speed Configuration
 */
const uint8_t MOTOR_SPEED_STRAIGHT = 130;    // Speed for straight movement (forward/backward)
const uint8_t MOTOR_SPEED_TURN_LEFT = 255;   // Left turn speed (full power for pivot turn)
const uint8_t MOTOR_SPEED_TURN_RIGHT = 200;  // Right turn speed (reduced for mechanical balance)

#endif // CONSTANTS_H
