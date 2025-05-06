#include <iostream>
#include <gpiod.hpp>

int main() {
    gpiod::chip chip("gpiochip0");
    chip.get_line()
}