#include "BlinkyShield.h"
#include "mbed.h"

#define BLINKY_PIN D13
#define WAIT_TIME 10 // how long we wait on each color (milliseconds)
BlinkyShield* blinky_shield;

int main()
{
    uint32_t BLINKY_COLOR = CYAN;
    uint8_t BLINKY_COLOR_INTENSITY = 10;

    blinky_shield = new BlinkyShield(BLINKY_PIN);
    blinky_shield->setIntensity(10);

    while (1) {
        for (int wheel_pos = 0; wheel_pos < 255; wheel_pos++) {
            for (int i = 0; i < blinky_shield->numPixels(); i++) {
                uint16_t color = blinky_shield->colorWheel((wheel_pos + i)%255);
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
