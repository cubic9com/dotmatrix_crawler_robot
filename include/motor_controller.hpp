#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

#include <Arduino.h>
#include "constants.h"

/**
 * MotorController Class
 * 
 * Controls a crawler robot using a TB6612FNG dual motor driver.
 * The class provides methods for basic robot movements: forward, backward,
 * left turn, and right turn. Motor directions are controlled via digital pins,
 * while speed is controlled using PWM signals.
 */
class MotorController {
public:
    MotorController() = default;

    /**
     * Initialize motor controller pins
     */
    void begin() {
        pinMode(PWMA, OUTPUT);
        pinMode(AIN2, OUTPUT);
        pinMode(AIN1, OUTPUT);
        pinMode(STBY, OUTPUT);
        pinMode(BIN1, OUTPUT);
        pinMode(BIN2, OUTPUT);
        pinMode(PWMB, OUTPUT);
        digitalWrite(STBY, HIGH);  // Enable motor driver
    }

    /**
     * Stop both motors
     */
    void stop() {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    }

    /**
     * Move the robot forward
     */
    void moveForward() {
        setMotorSpeed(MOTOR_SPEED_STRAIGHT, MOTOR_SPEED_STRAIGHT);
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }

    /**
     * Move the robot backward
     */
    void moveBackward() {
        setMotorSpeed(MOTOR_SPEED_STRAIGHT, MOTOR_SPEED_STRAIGHT);
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }

    /**
     * Turn the robot left
     */
    void turnLeft() {
        setMotorSpeed(MOTOR_SPEED_TURN_LEFT, MOTOR_SPEED_TURN_LEFT);
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }

    /**
     * Turn the robot right
     */
    void turnRight() {
        setMotorSpeed(MOTOR_SPEED_TURN_RIGHT, MOTOR_SPEED_TURN_RIGHT);
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }

private:
    /**
     * Set motor speeds using PWM
     * 
     * @param speedA PWM value for motor A (0-255)
     * @param speedB PWM value for motor B (0-255)
     */
    void setMotorSpeed(uint8_t speedA, uint8_t speedB) {
        analogWrite(PWMA, speedA);
        analogWrite(PWMB, speedB);
    }
};

#endif // MOTOR_CONTROLLER_HPP
