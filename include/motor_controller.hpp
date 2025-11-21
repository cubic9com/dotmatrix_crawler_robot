#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

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
    /**
     * Motor Speed Configuration
     * These values can be adjusted based on your robot's characteristics
     */
    struct MotorSpeed {
        uint8_t motorA;
        uint8_t motorB;
    };

    static constexpr MotorSpeed SPEED_FORWARD = {130, 255};
    static constexpr MotorSpeed SPEED_BACKWARD = {130, 195};
    static constexpr MotorSpeed SPEED_TURN_LEFT = {130, 255};
    static constexpr MotorSpeed SPEED_TURN_RIGHT = {130, 195};

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
     * Execute movement command based on direction
     * 
     * @param direction Movement direction from constants.h
     */
    void executeCommand(Direction direction) {
        switch (direction) {
        case Direction::STOP:
            stop();
            break;
        case Direction::FORWARD:
            moveForward();
            break;
        case Direction::BACKWARD:
            moveBackward();
            break;
        case Direction::LEFT:
            turnLeft();
            break;
        case Direction::RIGHT:
            turnRight();
            break;
        default:
            // Unknown command: stop for safety
            stop();
            break;
        }
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
        setMotorSpeed(SPEED_FORWARD.motorA, SPEED_FORWARD.motorB);
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }

    /**
     * Move the robot backward
     */
    void moveBackward() {
        setMotorSpeed(SPEED_BACKWARD.motorA, SPEED_BACKWARD.motorB);
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }

    /**
     * Turn the robot left
     */
    void turnLeft() {
        setMotorSpeed(SPEED_TURN_LEFT.motorA, SPEED_TURN_LEFT.motorB);
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
    }

    /**
     * Turn the robot right
     */
    void turnRight() {
        setMotorSpeed(SPEED_TURN_RIGHT.motorA, SPEED_TURN_RIGHT.motorB);
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
    }

private:
    /**
     * Motor Control Pin Definitions
     */
    // Motor A PWM control (speed control)
    static constexpr uint8_t PWMA = D0;
    // Motor A direction control pins
    static constexpr uint8_t AIN2 = D1;
    static constexpr uint8_t AIN1 = D2;
    // Standby pin (HIGH = motors enabled, LOW = motors disabled)
    static constexpr uint8_t STBY = D10;
    // Motor B direction control pins
    static constexpr uint8_t BIN1 = D3;
    static constexpr uint8_t BIN2 = D4;
    // Motor B PWM control (speed control)
    static constexpr uint8_t PWMB = D5;

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
