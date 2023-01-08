#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iomanip>
#include <stdint.h>
#include "Chip8.h"

Chip8::Chip8(std::string romPath)
    : romPath(romPath)
{
    std::fill(memory.begin(), memory.end(), 0);
    std::fill(display.begin(), display.end(), 0);
    std::fill(keypad.begin(), keypad.end(), 0);
    std::fill(V.begin(), V.end(), 0);
    loadROM();
    LoadFonts();

    gfx = new Graphics(10);
    gfx->createWindow("Chip-8 Emulator");
}

Chip8::~Chip8()
{
    delete gfx;
}

void Chip8::loadROM()
{
    std::ifstream input(romPath, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    // Load the ROM contents into the Chip8's memory, starting at 0x200
    for (long i = 0; i < buffer.size(); ++i)
    {
        memory[PC_START_ADDRESS + i] = buffer[i];
    }
}

void Chip8::LoadFonts()
{
    for (uint32_t i = 0; i < FONT_START_ADDRESS; i++)
    {
        memory[FONT_START_ADDRESS + i] = fontData[i];
    }
}

void Chip8::loop()
{
    bool running = true;
    while (running)
    {
        sf::Event event;
        while (gfx->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gfx->close();
                running = false;
            }
        }
        fetch();
        decodeExecute();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void Chip8::fetch()
{
    opcode = memory[pc + 1] | (memory[pc] << 8u);
    opcodeNibbles[0] = (opcode & 0xF000u) >> 12u;
    opcodeNibbles[1] = (opcode & 0x0F00u) >> 8u;
    opcodeNibbles[2] = (opcode & 0x00F0u) >> 4u;
    opcodeNibbles[3] = (opcode & 0x000Fu);
    opcodeNibbles[4] = (opcode & 0x00FFu); // xxNN last 2 hex digits
    opcodeNibbles[5] = (opcode & 0x0FFFu); // xNNN last 3 hex digits
    pc += 2;
}

void Chip8::decodeExecute()
{
    switch (opcodeNibbles[0])
    {
    case 0x0:
        switch (opcodeNibbles[5])
        {
        case 0x0E0:
            OP_00E0();
            IMPLEMENTED();
            return;
        case 0x0EE:
            NOT_IMPLEMENTED();
            return;
        default:
            NOT_IMPLEMENTED();
            return;
        }
    case 0x1:
        OP_1NNN();
        IMPLEMENTED();
        return;

    case 0x6:
        OP_6XNN();
        IMPLEMENTED();
        return;

    case 0x7:
        OP_7XNN();
        IMPLEMENTED();
        return;

    case 0xA:
        OP_ANNN();
        IMPLEMENTED();
        return;

    case 0xD:
        OP_DXYN();
        IMPLEMENTED();
        return;

    default:
        NOT_IMPLEMENTED();
        return;
    }
}

void Chip8::OP_00E0() // clear screen
{
    std::fill(display.begin(), display.end(), 0);
}

void Chip8::OP_1NNN() // jmp
{
    pc = opcodeNibbles[5];
}

void Chip8::OP_6XNN() // set register X
{
    V[opcodeNibbles[1]] = opcodeNibbles[4];
}

void Chip8::OP_7XNN()
{
    V[opcodeNibbles[1]] += opcodeNibbles[4];
}

void Chip8::OP_ANNN()
{
    I = opcodeNibbles[5];
}

void Chip8::OP_DXYN()
{
    uint8_t VX = V[opcodeNibbles[1]];
    uint8_t VY = V[opcodeNibbles[2]];
    uint8_t height = opcodeNibbles[3];

    // screen wrap
    uint8_t xPos = VX % 64;
    uint8_t yPos = VY % 32;

    V[0xF] = 0;

    for (uint row = 0; row < height; ++row)
    {
        uint8_t spriteByte = memory[I + row];

        for (uint col = 0; col < 8; ++col)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint8_t *screenPixel = &display[(xPos + col) + ((yPos + row) * 64)];

            if (spritePixel)
            {
                if (*screenPixel == 0xFFFFFFFF)
                {
                    V[0xF] = 1;
                }

                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
    gfx->windowClear();
    gfx->drawPixels(&display);
    gfx->windowDisplay();
}

void Chip8::IMPLEMENTED()
{
    std::cout << std::setfill('0') << std::setw(4) << std::right << std::hex << opcode;
    std::cout << " IMPLEMENTED\n";
}

void Chip8::NOT_IMPLEMENTED()
{
    std::cout << std::setfill('0') << std::setw(4) << std::right << std::hex << opcode;
    std::cout << " NOT IMPLEMENTED\n";
}