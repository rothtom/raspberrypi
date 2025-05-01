#include <wiringPi.h>
#include <iostream>

#define LEDPin 5

int main() {
    wiringPiSetup();

    pinMode(LEDPin, OUTPUT);
    digitalWrite(LEDPin, LOW);

    while (true) {
        digitalWrite(LEDPin, HIGH);
        std::cout << "HIGH" << std::endl;
        delay(1000);
        digitalWrite(LEDPin, LOW);
        std::cout << "LOW" << std::endl;
        delay(1000);
    }
    

    return 0;
}
