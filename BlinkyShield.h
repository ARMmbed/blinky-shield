#ifndef BLINKYSHIELD_H
#define BLINKYSHIELD_H

#include "mbed.h"
#include "PixelArray.h"
#include "WS2812.h"
#include "Adafruit_GFX.h"

#define STRIPLEN 40

#define RED (0x1f << 11)
#define GREEN (0x3f << 5)
#define BLUE (0x1f)
#define YELLOW RED|GREEN
#define MAGENTA RED|BLUE
#define CYAN GREEN|BLUE
#define WHITE RED|GREEN|BLUE

class BlinkyShield : public Adafruit_GFX
{
public:
    BlinkyShield(PinName pin=D6);
    ~BlinkyShield();
    void wipeColor(uint16_t color, uint8_t n_pixels=STRIPLEN);
    void red(uint8_t n_pixels=STRIPLEN);
    void green(uint8_t n_pixels=STRIPLEN);
    void blue(uint8_t n_pixels=STRIPLEN);
    void off();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void scroll(const char *fmt, ...);
    void clear();
    void setIntensity(uint8_t intensity);
    uint16_t colorCvt(uint32_t color);
    uint32_t colorCvtRev(uint16_t color);
    uint16_t color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t numPixels();
    void setPixelColor(uint8_t x, uint8_t y, uint16_t color);
    void setPixelColor(uint16_t n, uint16_t color);
    void show();

private:
    PixelArray* _px;
    WS2812* _shield;
};
#endif
