#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

/**
 * Direction Constants
 * Using enum class for type safety and namespace isolation
 */
enum class Direction : uint8_t {
    STOP = 0,     // Stop all motors
    FORWARD = 1,  // Move forward
    BACKWARD = 2, // Move backward
    LEFT = 3,     // Turn left (left motor backward, right motor forward)
    RIGHT = 4     // Turn right (right motor backward, left motor forward)
};

#endif // CONSTANTS_H
