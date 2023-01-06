#include <string>
#include <SFML/System/Time.hpp>
#include "Chip8.h"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::string fp(argv[1]);
        Chip8 chip8(fp);
        chip8.loop();

        return 0;
    }

    return 0;
}