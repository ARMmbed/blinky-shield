#include "BlinkyShield.h"
#include "mbed.h"

#define BLINKY_PIN D13
#define WAIT_TIME 10 // how long we wait on each color (milliseconds)
BlinkyShield* blinky_shield;

int main()
{
    blinky_shield = new BlinkyShield(BLINKY_PIN);
    blinky_shield->setIntensity(10);

    uint8_t green; // brightness of the green 
    uint8_t red;  // add a bit for red
    while (1) {
        green = 50 + rand() % 155;
        red = green + rand() % 50;
        uint16_t c = blinky_shield->color(red, green, 0);
        uint8_t n = rand() % blinky_shield->numPixels();
        blinky_shield->setPixelColor(n, c);
        blinky_shield->show();
        wait_ms(5);
    }

    /* code */
    return 0;
}
