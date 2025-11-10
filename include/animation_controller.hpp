#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include <LovyanGFX.hpp>
#include "constants.h"
#include "arrow_images.h"

/**
 * AnimationController Class
 * 
 * Manages animated arrow displays on the LED matrix to indicate robot direction.
 * The class cycles through 12 animation frames for each direction, creating
 * smooth animated arrows.
 * 
 * Animation Structure:
 * - 4 arrow types (forward, backward, left, right)
 * - 12 frames per animation cycle
 */
class AnimationController {
public:
    AnimationController() : animCounter(0) {}

    /**
     * Update animation frame and display arrow
     * 
     * @param sprite LovyanGFX sprite to draw the arrow on
     * @param direction Current movement direction (from constants.h)
     */
    void update(LGFX_Sprite& sprite, uint8_t direction) {
        animCounter++;
        if (animCounter >= ANIMATION_FRAMES) {
            animCounter = 0;
        }

        // Display arrow based on direction
        switch (direction) {
        case DIRECTION_FORWARD:
            displayArrow(sprite, 0);  // Upward arrow
            break;
        case DIRECTION_BACKWARD:
            displayArrow(sprite, 1);  // Downward arrow
            break;
        case DIRECTION_LEFT:
            displayArrow(sprite, 2);  // Leftward arrow
            break;
        case DIRECTION_RIGHT:
            displayArrow(sprite, 3);  // Rightward arrow
            break;
        default:
            sprite.clear();  // Stop: clear display
            break;
        }
    }

    /**
     * Reset animation counter to first frame
     */
    void reset() {
        animCounter = 0;
    }

private:
    // Number of frames in each animation cycle
    static constexpr uint8_t ANIMATION_FRAMES = 12;
    // Current animation frame (0-11)
    uint8_t animCounter;

    /**
     * Display a specific arrow frame on the sprite
     * 
     * @param sprite LovyanGFX sprite to draw on
     * @param arrowType Arrow direction type (0-3)
     */
    void displayArrow(LGFX_Sprite& sprite, uint8_t arrowType) {
        sprite.pushImage(0, 0, ARROW_WIDTH, ARROW_HEIGHT, 
                        (lgfx::rgb565_t*)arrowImg[arrowType][animCounter]);
    }
};

#endif // ANIMATION_CONTROLLER_HPP
