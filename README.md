
# Keyestudio 2812 Shield Matrix 8x5 RGB LED
## Introduction 
The **Keyestudio 2812 Shield** Matrix 8x5 RGB LED is composed of 40 individually addressable 24-bit color LEDs. It adopts stackable design compatible with [UNO board](https://store.arduino.cc/usa/arduino-uno-rev3). It is an intelligent control LED light source that the control circuit and RGB chip are integrated in a 5050 SMD component. It includes intelligent digital port data latch and signal reshaping amplification drive circuit. Also includes a precision internal oscillator and a 12V programmable constant current control part, effectively ensuring the highly consistency of the pixel point light color.
The data transfer protocol uses single [NZR communication mode](https://en.wikipedia.org/wiki/Non-return-to-zero). After the pixel 
power-on reset, the DI port receives data from controller, the first pixel collect initial 24bit data then sent to the internal data latch.
LED with advantages of low driving voltage, environmental-friendly, energy saving high brightness, large scattering angle, good consistency, long life span etc.

![alt text](https://cdn-shop.adafruit.com/1200x900/1430-00.jpg)

## LED Specification 
- Data sending speed can reach 800Kbps
- When the refresh rate is 30fps, cascade number no less than 1024 points
- The color of the light is highly consistent, cost-effective
- Built-in power on reset circuit and power-down reset circuit
-  Each pixel of the three primary color can achieve 256 brightness display, completed 16777216 color full color display, scan frequency no less than 400Hz/s
- Anti-reverse protection circuit, the reverse of power supply will not damage the internal IC of the LED
- Built-in signal reshaping circuit, signals received will be wave-reshaped first and then output to the next driver, ensuring wave-form distortion to not accumulate
- IC control circuit and LED point light source uses the same power supply
- Serial cascade interface, via a signal line to complete the reception and decoding of data 
- When transmission distance between two arbitrary points is no more than five meters, no extra circuit needed
- Control circuit and the RGB chip are integrated in a 5050 SMD component, forming a complete control of pixel point

## Example test
1. Import the following [files](https://github.com/ARMmbed/blinky-shield) into an [online compiler](https://os.mbed.com/compiler/) 
2. Create a main.cpp and paste the following code:

```cpp
#include "mbed.h"
#include "BlinkyShield.h"
int main()
{
    BlinkyShield* blinky_shield;
    uint32_t BLINKY_COLOR = CYAN;
    uint8_t BLINKY_COLOR_INTENSITY = 10;
    #define BLINKY_PIN D13

    blinky_shield = new BlinkyShield(BLINKY_PIN);
    blinky_shield->setIntensity(10);

    blinky_shield->red();
    wait_ms(500);
    blinky_shield->green();
    wait_ms(500);
    blinky_shield->blue();
    wait_ms(500);
    blinky_shield->off();
    wait_ms(500);
    blinky_shield->wipeColor(BLINKY_COLOR);
    wait_ms(500);
    blinky_shield->clear();
    blinky_shield->setTextColor(BLINKY_COLOR);
    blinky_shield->putc('A');
    wait_ms(500);
    blinky_shield->clear();
    blinky_shield->setCursor(1, 1);
    blinky_shield->putc('B');
    wait_ms(500);
    blinky_shield->clear();
    blinky_shield->setCursor(2, 1);
    blinky_shield->putc('C');
    wait_ms(500);
    blinky_shield->clear();
    blinky_shield->setCursor(3, 1);
    blinky_shield->putc('D');

    int number = 1;
    wait_ms(500);
    blinky_shield->clear();
    blinky_shield->scroll("armMbed %i", number);
    /* code */
    return 0; 
    }

```
3. Compile the program
4. Connect the board via USB then use the following code in the terminal to communicate with the board:
```cpp
sudo cu -l /dev/tty.usbmodem -s 9600
```
5. Place cursor at the end of 'usbmodem' and press tab 
6. Use one of the given numbers as your port
7. Transfer the compiled program to the board






Shazman
@LiyouZhou
