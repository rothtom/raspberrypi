#include <pigpio.h>
#include <iostream>

#define LEDPin 17

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "Initialisation failed" << std::endl;
        return 1;
    }
    
    gpioSetMode(LEDPin, PI_OUTPUT);

    while(true) {
        gpioWrite(LEDPin, 1);
        gpioSleep(PI_TIME_RELATIVE, 1, 1);
        gpioWrite(LEDPin, 0);
        gpioSleep(PI_TIME_RELATIVE, 1, 1);
    }

    return 0;
}
