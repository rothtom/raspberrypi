#include <iostream>
#include <gpiod.hpp>
#include <array>
#include <vector>
#include <chrono>
#include <thread>

int main() {
    gpiod::chip chip("gpiochip0");
    
    std::array<std::array<char, 4>, 4> num_fields = {{
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
    }};
    
    std::array<unsigned int, 8> line_offsets = {10, 22, 27, 17, 18, 23, 24, 25};
    
    std::array<gpiod::line, 8> lines;
    for (int i=0; i<4; i++) {
        lines[i] = chip.get_line(line_offsets[i]);
        lines[i].request({
            .consumer = "ouput " + i,
            .request_type = gpiod::line_request::DIRECTION_OUTPUT
        }, 0);
    }

    for (int i=0; i<4; i++) {
        lines[i+4] = chip.get_line(line_offsets[i+4]);
        lines[i+4].request({
            .consumer = "input " + i,
            .request_type = gpiod::line_request::DIRECTION_INPUT
        });
    }

    int row = -1;
    int collumn = -1;

    while (true) {
        bool active = false;        
        for (int c=0; c<4; c++) {
            for (int i=0; i<4; i++) {
                if (i != c) {
                    lines[i].set_value(gpiod::line::ACTIVE_LOW);
                }
                else {
                    lines[i].set_value(0);
                }
            }
            
            for (int i=0; i<4; i++) {
                if (lines[i+4].get_value() == 1) {
                    row = i;
                    
                    active = true;
                    break;
                }
            }
            if (!active) {
                collumn = c;
            }
        }
        if (active) {
            std::cout << "Row: " << row << "Collumn: " << collumn << std::endl;
        }
        active = false;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (auto line : lines) {
        line.release();
    }
    chip.reset();
}