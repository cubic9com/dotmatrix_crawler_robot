/**
 * Controller for a Crawler Robot Equipped with a Dot-Matrix Display 
 *
 * This program controls a crawler robot with a 16x16 LED matrix display.
 * The robot receives movement commands via ESP-NOW wireless protocol and
 * displays animated directional arrows on the LED matrix to indicate
 * its current movement direction.
 *
 * Hardware Components:
 * - Seeed Studio XIAO ESP32-C6 microcontroller
 * - Toshiba TB6612FNG dual motor driver
 * - Two DC motors
 * - 16x16 WS2812 LED matrix
 *
 * Communication:
 * - Uses ESP-NOW protocol for receiving direction commands
 * - Commands include: STOP, FORWARD, BACKWARD, LEFT, RIGHT
 *
 * Features:
 * - Real-time motor control based on received commands
 * - Animated arrow display showing current direction
 * - 12-frame animation cycle for smooth visual feedback
 */

#include <FastLED.h>
#include <LovyanGFX.hpp>
#include <esp_now.h>
#include <WiFi.h>
#include "constants.h"
#include "motor_controller.hpp"
#include "led_display.hpp"
#include "animation_controller.hpp"

/**
 * ESP-NOW Message Structure
 */
typedef struct MessageStruct {
    uint8_t direction; // Movement direction command
} MessageStruct;

/**
 * Global Objects and Variables
 */
MessageStruct messageData = {
    .direction = DIRECTION_STOP
};
LGFX_Sprite arrowSprite;                 // 16x16 sprite for arrow rendering
MotorController motorController;         // Motor control interface
LedDisplay ledDisplay;                   // LED matrix interface
AnimationController animationController; // Animation manager

void handleDirectionChange(uint8_t direction);

/**
 * ESP-NOW Data Reception Callback
 *
 * @param esp_now_info Information about the sender (not used)
 * @param incomingData Pointer to received data buffer
 * @param len Length of received data in bytes
 */
void OnDataRecv(const esp_now_recv_info_t *esp_now_info, const uint8_t *incomingData, int len) {
    // Validate data size matches our message structure
    if (len != sizeof(MessageStruct)) {
        return;
    }

    // Copy received data into our structure
    memcpy(&messageData, incomingData, len);
    Serial.printf("Received direction: %d\n", messageData.direction);

    // Reset animation to start from first frame for new direction
    animationController.reset();
    // Execute motor control command
    handleDirectionChange(messageData.direction);
}

/**
 * Handle Direction Change
 *
 * Translates received direction commands into motor control actions.
 * Each direction command triggers specific motor movements:
 * - STOP: Brake both motors
 * - FORWARD: Both motors forward
 * - BACKWARD: Both motors backward
 * - LEFT: Pivot turn (left motor back, right motor forward)
 * - RIGHT: Pivot turn (right motor back, left motor forward)
 *
 * @param direction Direction command from constants.h
 */
void handleDirectionChange(uint8_t direction) {
    switch (direction) {
    case DIRECTION_STOP:
        motorController.stop();
        break;
    case DIRECTION_FORWARD:
        motorController.moveForward();
        break;
    case DIRECTION_BACKWARD:
        motorController.moveBackward();
        break;
    case DIRECTION_LEFT:
        motorController.turnLeft();
        break;
    case DIRECTION_RIGHT:
        motorController.turnRight();
        break;
    default:
        // Unknown command: stop for safety
        motorController.stop();
        break;
    }
}

/**
 * Initialize ESP-NOW Communication
 *
 * @return true if initialization successful, false otherwise
 */
bool initESPNow() {
    // Set WiFi to station mode (required for ESP-NOW)
    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW protocol
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW initialization failed");
        return false;
    }

    // Register callback function for receiving data
    esp_now_register_recv_cb(OnDataRecv);

    return true;
}

/**
 * Setup Function
 */
void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Initialize motor controller pins and enable motor driver
    motorController.begin();

    // Initialize LED matrix sprite and display
    arrowSprite.setColorDepth(16);                                 // 16-bit color (RGB565)
    arrowSprite.createSprite(LED_MATRIX_WIDTH, LED_MATRIX_HEIGHT); // Create 16x16 pixel sprite
    ledDisplay.begin();

    // Initialize ESP-NOW wireless communication
    if (!initESPNow()) {
        // Critical failure: stop execution to prevent unsafe operation
        Serial.println("Failed to initialize ESP-NOW. System halted.");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("Setup complete - Robot ready");
}

/**
 * Main Loop Function
 */
void loop() {
    // Update animation frame and render arrow to sprite
    animationController.update(arrowSprite, messageData.direction);

    // Display sprite contents on LED matrix
    ledDisplay.show(arrowSprite);

    // Delay for animation timing (200ms = 5 frames per second)
    delay(200);
}
