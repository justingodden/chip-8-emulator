#include <iostream>
#include <string>
#include <SFML/System/Time.hpp>
#include "Chip8.h"
#include "Disassembler.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        Chip8 chip8(std::string(argv[1]));

        return 0;
    }

    return 0;
}