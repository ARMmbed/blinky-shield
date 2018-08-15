#include "mbed.h"
#include "BlinkyShield.h"
#include "PixelArray.h"
#include "WS2812.h"
#include "string.h"
#include "stdio.h"

BlinkyShield::BlinkyShield(PinName pin)
: Adafruit_GFX(5, 8)
{
    _shield = new WS2812((PinName)pin, STRIPLEN,
        MBED_CONF_BLINKY_SHIELD_WS2812_ZERO_HIGH,
        MBED_CONF_BLINKY_SHIELD_WS2812_ZERO_LOW,
        MBED_CONF_BLINKY_SHIELD_WS2812_ONE_HIGH,
        MBED_CONF_BLINKY_SHIELD_WS2812_ONE_LOW);
    _px = new PixelArray(STRIPLEN);
    off();
}

BlinkyShield::~BlinkyShield()
{
    delete _shield;
    delete _px;
}

void BlinkyShield::setIntensity(uint8_t intensity)
{
    _shield->useII(WS2812::GLOBAL);
    _shield->setII(intensity);
}

void BlinkyShield::wipeColor(uint16_t color, uint8_t n_pixels)
{
    uint32_t c = colorCvtRev(color);
    for (uint8_t i = 0; i < STRIPLEN; i++)
    {
        if (i < n_pixels)
        {
            _px->Set(i, c & 0xffffff);
        }
        else
        {
            _px->Set(i, 0);
        }
    }
    _shield->write_offsets(_px->getBuf(),0,0,0);
}

void BlinkyShield::red(uint8_t n_pixels)
{
    wipeColor(RED, n_pixels);
}

void BlinkyShield::green(uint8_t n_pixels)
{
    wipeColor(GREEN, n_pixels);
}

void BlinkyShield::blue(uint8_t n_pixels)
{
    wipeColor(BLUE, n_pixels);
}

void BlinkyShield::off()
{
    wipeColor(0);
}

void BlinkyShield::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if ((x >= this->width()) || (y >= this->height()))
        return;

    uint8_t n = y + (this->width() - x - 1) * this->height();

    _px->Set(n, colorCvtRev(color));
    _shield->write_offsets(_px->getBuf(),0,0,0);
}


void BlinkyShield::scroll(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    const uint8_t max_str_len = 100;
    char s[max_str_len] = {0};
    vsnprintf(s, max_str_len, fmt, args);
    uint8_t len = strnlen(s, max_str_len);
    int len_in_px = len * 6;
    this->setTextWrap(false);
    for (int x = this->width(); x > -len_in_px; --x)
    {
        this->clear();
        this->setCursor(x, 1);
        this->printf(s);
        wait_ms(200);
    }
    va_end(args);
}

void BlinkyShield::clear()
{
    this->off();
    this->setCursor(0, 0);
}

uint16_t BlinkyShield::colorCvt(uint32_t color)
{
    uint32_t r = (color >> 16 & 0xff) * 0x1f / 0xff;
    uint32_t g = (color >> 8  & 0xff) * 0x3f / 0xff;
    uint32_t b = (color >> 0  & 0xff) * 0x1f / 0xff;

    return r << 11 | g << 5 | b;
}

uint32_t BlinkyShield::colorCvtRev(uint16_t color)
{
    uint32_t r = (color >> 11 & 0x1f) * 0xff / 0x1f;
    uint32_t g = (color >> 5  & 0x3f) * 0xff / 0x3f;
    uint32_t b = (color >> 0  & 0x1f) * 0xff / 0x1f;

    return r << 16 | g << 8 | b;
}

uint16_t BlinkyShield::color(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t r_prime = (r & 0xff) << 16;
    uint32_t g_prime = (g & 0xff) << 8;
    uint32_t b_prime = (b & 0xff) << 0;

    return colorCvt(r_prime | g_prime | b_prime);
}

uint32_t BlinkyShield::numPixels()
{
    return 40;
}

void BlinkyShield::setPixelColor(uint8_t x, uint8_t y, uint16_t color)
{
    if ((x >= this->width()) || (y >= this->height()))
        return;

    uint8_t n = y + (this->width() - x - 1) * this->height();

    this->setPixelColor(n, color);
}

void BlinkyShield::setPixelColor(uint16_t n, uint16_t color)
{
    _px->Set(n, colorCvtRev(color));
}

void BlinkyShield::show()
{
    _shield->write(_px->getBuf());
}
