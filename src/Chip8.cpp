#include <fstream>
#include <stdint.h>
#include "Chip8.h"

Chip8::Chip8(std::string romPath)
    : romPath(romPath)
{
    pc = PC_START_ADDRESS;
    loadROM();
    LoadFonts();

    gfx = new Graphics;
    gfx->createWindow(64, 32, "Chip-8 Emulator");
}

Chip8::~Chip8()
{
    delete gfx;
}

void Chip8::loadROM()
{
    std::ifstream file(romPath, std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        // Get size of file and allocate a buffer to hold the contents
        std::streampos size = file.tellg();
        char *buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // Load the ROM contents into the Chip8's memory, starting at 0x200
        for (long i = 0; i < size; ++i)
        {
            memory[PC_START_ADDRESS + i] = buffer[i];
        }

        // Free the buffer
        delete[] buffer;
    }
}

void Chip8::LoadFonts()
{
    for (uint32_t i = 0; i < FONT_START_ADDRESS; i++)
    {
        memory[FONT_START_ADDRESS + i] = fontData[i];
    }
}