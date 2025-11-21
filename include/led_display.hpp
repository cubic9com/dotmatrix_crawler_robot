#ifndef LED_DISPLAY_HPP
#define LED_DISPLAY_HPP

#include <FastLED.h>
#include <LovyanGFX.hpp>

/**
 * LedDisplay Class
 * 
 * Controls a 16x16 WS2812 LED matrix display using the FastLED library.
 * The display shows animated arrow graphics rendered by LovyanGFX.
 * 
 * LED Matrix Layout:
 * The LEDs are arranged in a zigzag pattern where even rows run left-to-right
 * and odd rows run right-to-left. This is a common wiring pattern for LED matrices
 * to minimize wire length.
 */
class LedDisplay {
public:
    // LED matrix dimensions
    static constexpr uint8_t LED_MATRIX_HEIGHT = 16;
    static constexpr uint8_t LED_MATRIX_WIDTH = 16;

    LedDisplay() = default;

    /**
     * Initialize the LED matrix
     */
    void begin() {
        // Apply color correction for more natural white balance
        auto correction = CRGB(0xFF, 0xFF, 0xF3);
        FastLED.addLeds<WS2812B, LED_DIN, GRB>(leds, LED_MATRIX_NUM_LEDS).setCorrection(correction);
        FastLED.setBrightness(LED_BRIGHTNESS);
    }

    /**
     * Display sprite contents on the LED matrix
     * 
     * @param sprite LovyanGFX sprite containing the image to display
     */
    void show(LGFX_Sprite& sprite) {
        // Iterate through each pixel in the sprite
        for (auto y = 0; y < LED_MATRIX_WIDTH; y++) {
            for (auto x = 0; x < LED_MATRIX_WIDTH; x++) {
                // Read pixel color from sprite (RGB888 format)
                auto rgb888 = sprite.readPixelRGB(x, y);
                // Convert to FastLED CRGB format
                auto rgb = CRGB(rgb888.r, rgb888.g, rgb888.b);

                // Rotate coordinates 90° (swap x and y)
                auto ix = y;
                auto iy = x;
                // Map to zigzag LED array index
                // Even rows: left to right, Odd rows: right to left
                leds[(iy % 2 ? LED_MATRIX_WIDTH - ix - 1 : ix) + iy * LED_MATRIX_WIDTH] = rgb;
            }
        }

        // Update the physical LED matrix
        FastLED.show();
    }

private:
    /**
     * LED Matrix Configuration
     */
    // Data input pin for LED matrix
    static constexpr uint8_t LED_DIN = D7;
    // Total number of LEDs in the matrix
    static constexpr uint16_t LED_MATRIX_NUM_LEDS = LED_MATRIX_WIDTH * LED_MATRIX_HEIGHT;
    // LED brightness level (0-255, set to ~5% to reduce power consumption)
    static constexpr uint8_t LED_BRIGHTNESS = 13;

    // LED array buffer
    CRGB leds[LED_MATRIX_NUM_LEDS];
};

#endif // LED_DISPLAY_HPP
