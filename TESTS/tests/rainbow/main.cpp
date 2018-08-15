#include "BlinkyShield.h"
#include "mbed.h"

#define BLINKY_PIN D13
#define WAIT_TIME 10 // how long we wait on each color (milliseconds)
BlinkyShield* blinky_shield;

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(uint8_t WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return blinky_shield->color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return blinky_shield->color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return blinky_shield->color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

int main()
{
    uint32_t BLINKY_COLOR = CYAN;
    uint8_t BLINKY_COLOR_INTENSITY = 10;

    blinky_shield = new BlinkyShield(BLINKY_PIN);
    blinky_shield->setIntensity(10);

    while (1) {
        for (int wheel_pos = 0; wheel_pos < 255; wheel_pos++) {
            for (int i = 0; i < blinky_shield->numPixels(); i++) {
                uint16_t color = Wheel((wheel_pos + i)%255);
                // printf("color %x %u %u\r\n", color, wheel_pos, i);
                blinky_shield->setPixelColor(i, color);
            }
            blinky_shield->show();
            wait_ms(WAIT_TIME);
        }
    }

    /* code */
    return 0;
}
