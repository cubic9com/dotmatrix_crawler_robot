#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include <LovyanGFX.hpp>
#include "arrow_images.h"
#include "constants.h"

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
    /**
     * Update animation frame and display arrow
     * 
     * @param sprite LovyanGFX sprite to draw the arrow on
     * @param direction Current movement direction (from constants.h)
     */
    void update(LGFX_Sprite& sprite, Direction direction) {
        animCounter++;
        if (animCounter >= ANIMATION_FRAMES) {
            animCounter = 0;
        }

        // Display arrow based on direction
        switch (direction) {
        case Direction::FORWARD:
            displayArrow(sprite, 0);  // Upward arrow
            break;
        case Direction::BACKWARD:
            displayArrow(sprite, 1);  // Downward arrow
            break;
        case Direction::LEFT:
            displayArrow(sprite, 2);  // Leftward arrow
            break;
        case Direction::RIGHT:
            displayArrow(sprite, 3);  // Rightward arrow
            break;
        default:
            sprite.clear();
            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 16; y++) {
                    switch (rand() % 10) {
                        case 0:
                            sprite.setColor(sprite.color565(153, 132, 0));
                            sprite.drawPixel(x, y);
                            break;
                        case 1:
                            sprite.setColor(sprite.color565(102, 81, 0));
                            sprite.drawPixel(x, y);
                            break;
                        case 2:
                            sprite.setColor(sprite.color565(51, 30, 0));
                            sprite.drawPixel(x, y);
                            break;
                        default:
                            break;
                    }
                }
            }
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
    uint8_t animCounter = 0;

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
