#include <iostream>
#include <gpiod.hpp>
#include <array>

int main() {

    gpiod::chip chip("gpiochip0");

    std::array<gpiod::line, 54> lines;
    for (int i=0; i<28; i++) {
        lines[i] = chip.get_line(i);
        lines[i].request({
            .consumer = "reset",
            .request_type = gpiod::line_request::DIRECTION_OUTPUT
        }, 0);
    }
    chip.reset();
}