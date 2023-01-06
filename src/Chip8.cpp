#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <stdint.h>
#include "Chip8.h"

Chip8::Chip8(std::string romPath)
    : romPath(romPath)
{
    pc = PC_START_ADDRESS;
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
    auto lastCycleTime = std::chrono::high_resolution_clock::now();

    while (true)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > clockDelay)
        {
            lastCycleTime = currentTime;
            fetch();
            decodeExecute();
        }
    }
}

void Chip8::fetch()
{
    opcode = (memory[pc + 1] << 8u) | memory[pc];
    opcodeNibbles[0] = (opcode & 0xF000u) >> 12;
    opcodeNibbles[1] = (opcode & 0xF00u) >> 8;
    opcodeNibbles[2] = (opcode & 0xF0u) >> 4;
    opcodeNibbles[3] = (opcode & 0xFu);
    opcodeNibbles[4] = (opcode & 0xFFu);  // xxNN last 2 hex digits
    opcodeNibbles[5] = (opcode & 0xFFFu); // xNNN last 3 hex digits
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
            break;
        case 0x0EE:
            NOT_IMPLEMENTED();
            break;
        default:
            NOT_IMPLEMENTED();
            break;
        }
    case 0x6:
        OP_6XNN();
        break;
    case 0x7:
        OP_7XNN();
        break;
    case 0xA:
        OP_ANNN();
        break;

    case 0xD:
        OP_DXYN();
        break;

    default:
        break;
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
    I = opcodeNibbles[5];
}

void Chip8::OP_ANNN()
{
    V[opcodeNibbles[1]] += opcodeNibbles[4];
}

void Chip8::OP_DXYN()
{
    gfx->windowClear();
    for (int i = 0; i < (32 * 64); i++)
    {
        if (display[i])
        {
            uint yPos = i / 64;
            uint xPos = i - (yPos * 64);
            gfx->drawPixel(xPos, yPos);
        }
    }
    gfx->windowDisplay();
}

void Chip8::NOT_IMPLEMENTED()
{
    std::cout << std::setfill('0') << std::setw(4) << std::right << std::hex << opcode;
    std::cout << " NOT IMPLEMENTED\n";
}