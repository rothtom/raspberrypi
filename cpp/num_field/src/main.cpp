#include <iostream>
#include <gpiod.hpp>
#include <array>
#include <vector>

int main() {
    gpiod::chip chip("gpiochip0");
    
    std::array<std::array<char, 4>, 4> num_fields = {{
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
    }};
    
    std::array<unsigned int, 8> line_offsets = {4, 17, 27, 22, 5, 6, 13, 19};
    
    std::array<gpiod::line, 8> lines;
    for (int i=0; i<8; i++) {
        lines[i] = chip.get_line(line_offsets[i]);
        lines[i].request({
            .consumer = "input " + i,
            .request_type = gpiod::line_request::DIRECTION_INPUT
        });
    }


}