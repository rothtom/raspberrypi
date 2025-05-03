#include <gpiod.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    try {
        // Open the GPIO chip by name (usually "gpiochip0" on Raspberry Pi)
        gpiod::chip chip("gpiochip0");

        // Get lines by GPIO offset number (BCM numbers)
        auto led_line = chip.get_line(5);     // BCM GPIO5
        auto button_line = chip.get_line(21); // BCM GPIO17

        // Request lines
        led_line.request(gpiod::line_request({
            .consumer = "led",
            .request_type = gpiod::line_request::DIRECTION_OUTPUT,
        }), 
            0);

        button_line.request(gpiod::line_request({
            .consumer = "button",
            .request_type= gpiod::line_request::DIRECTION_INPUT
        }));

        std::cout << "Monitoring button and controlling LED...\n";

        while (true) {
            int value = button_line.get_value();
            led_line.set_value(value == 1 ? 1 : 0); // LED on when button pressed
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    } catch (const std::exception& e) {
        std::cerr << "GPIO error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
