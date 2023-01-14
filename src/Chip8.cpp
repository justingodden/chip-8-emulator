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

    gfx = new Graphics(30);
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
    auto lastCycleTime = std::chrono::high_resolution_clock::now();

    while (running)
    {
        running = gfx->checkKeyPresses(keypad);

        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > 3)
        {
            lastCycleTime = currentTime;

            fetch();
            decodeExecute();

            if (delayTimer > 0)
            {
                delayTimer -= 1;
            }
            if (soundTimer > 0)
            {
                std::cout << '\a' << std::flush;
                soundTimer -= 1;
            }
        }
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
            OP_00EE();
            IMPLEMENTED();
            return;
        default:
            OP_0NNN();
            NOT_IMPLEMENTED();
            return;
        }
    case 0x1:
        OP_1NNN();
        IMPLEMENTED();
        return;

    case 0x2:
        OP_2NNN();
        IMPLEMENTED();
        return;

    case 0x3:
        OP_3XNN();
        IMPLEMENTED();
        return;

    case 0x4:
        OP_4XNN();
        IMPLEMENTED();
        return;

    case 0x5:
        OP_5XY0();
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

    case 0x8:
        switch (opcodeNibbles[3])
        {
        case 0x0:
            OP_8XY0();
            IMPLEMENTED();
            return;
        case 0x1:
            OP_8XY1();
            IMPLEMENTED();
            return;
        case 0x2:
            OP_8XY2();
            IMPLEMENTED();
            return;
        case 0x3:
            OP_8XY3();
            IMPLEMENTED();
            return;
        case 0x4:
            OP_8XY4();
            IMPLEMENTED();
            return;
        case 0x5:
            OP_8XY5();
            IMPLEMENTED();
            return;
        case 0x6:
            OP_8XY6();
            IMPLEMENTED();
            return;
        case 0x7:
            OP_8XY7();
            IMPLEMENTED();
            return;
        case 0xE:
            OP_8XYE();
            IMPLEMENTED();
            return;
        default:
            NOT_IMPLEMENTED();
            return;
        }

    case 0x9:
        OP_9XY0();
        IMPLEMENTED();
        return;

    case 0xA:
        OP_ANNN();
        IMPLEMENTED();
        return;

    case 0xB:
        OP_BNNN();
        IMPLEMENTED();
        return;

    case 0xC:
        OP_CXNN();
        IMPLEMENTED();
        return;

    case 0xD:
        OP_DXYN();
        IMPLEMENTED();
        return;

    case 0xE:
        switch (opcodeNibbles[4])
        {
        case 0x9E:
            OP_EX9E();
            IMPLEMENTED();
            return;
        case 0xA1:
            OP_EXA1();
            IMPLEMENTED();
            return;
        default:
            NOT_IMPLEMENTED();
            return;
        }

    case 0xF:
        switch (opcodeNibbles[4])
        {
        case 0x07:
            OP_FX07();
            IMPLEMENTED();
            return;
        case 0x0A:
            OP_FX0A();
            IMPLEMENTED();
            return;
        case 0x15:
            OP_FX15();
            IMPLEMENTED();
            return;
        case 0x18:
            OP_FX18();
            IMPLEMENTED();
            return;
        case 0x1E:
            OP_FX1E();
            IMPLEMENTED();
            return;
        case 0x29:
            OP_FX29();
            IMPLEMENTED();
            return;
        case 0x33:
            OP_FX33();
            IMPLEMENTED();
            return;
        case 0x55:
            OP_FX55();
            IMPLEMENTED();
            return;
        case 0x65:
            OP_FX65();
            IMPLEMENTED();
            return;
        default:
            NOT_IMPLEMENTED();
            return;
        }

    default:
        NOT_IMPLEMENTED();
        return;
    }
}

void Chip8::OP_0NNN()
{
}

void Chip8::OP_00E0() // clear screen
{
    std::fill(display.begin(), display.end(), 0);
}

void Chip8::OP_00EE()
{
    if (!stack.empty())
    {
        pc = std::move(stack.top());
        stack.pop();
    }
}

void Chip8::OP_1NNN() // jmp
{
    pc = opcodeNibbles[5];
}

void Chip8::OP_2NNN()
{
    stack.push(pc);
    pc = opcodeNibbles[5];
}

void Chip8::OP_3XNN()
{
    if (V[opcodeNibbles[1]] == opcodeNibbles[4])
    {
        pc += 2;
    }
}

void Chip8::OP_4XNN()
{
    if (V[opcodeNibbles[1]] != opcodeNibbles[4])
    {
        pc += 2;
    }
}

void Chip8::OP_5XY0()
{
    if (V[opcodeNibbles[1]] == V[opcodeNibbles[2]])
    {
        pc += 2;
    }
}

void Chip8::OP_6XNN() // set register X
{
    V[opcodeNibbles[1]] = opcodeNibbles[4];
}

void Chip8::OP_7XNN()
{
    V[opcodeNibbles[1]] += opcodeNibbles[4];
}

void Chip8::OP_8XY0()
{
    V[opcodeNibbles[1]] = V[opcodeNibbles[2]];
}

void Chip8::OP_8XY1()
{
    V[opcodeNibbles[1]] |= V[opcodeNibbles[2]];
}

void Chip8::OP_8XY2()
{
    V[opcodeNibbles[1]] &= V[opcodeNibbles[2]];
}

void Chip8::OP_8XY3()
{
    V[opcodeNibbles[1]] ^= V[opcodeNibbles[2]];
}

void Chip8::OP_8XY4()
{
    uint16_t sum = V[opcodeNibbles[1]] + V[opcodeNibbles[2]];

    if (sum > 255u)
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    V[opcodeNibbles[1]] += V[opcodeNibbles[2]];
}

void Chip8::OP_8XY5()
{
    if (V[opcodeNibbles[1]] > V[opcodeNibbles[2]])
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    V[opcodeNibbles[1]] -= V[opcodeNibbles[2]];
}

void Chip8::OP_8XY6()
{
    V[0xF] = (0x1u & V[opcodeNibbles[1]]);
    V[opcodeNibbles[1]] >>= 1;
}

void Chip8::OP_8XY7()
{
    if (V[opcodeNibbles[2]] > V[opcodeNibbles[1]])
    {
        V[0xF] = 1;
    }
    else
    {
        V[0xF] = 0;
    }

    V[opcodeNibbles[1]] = V[opcodeNibbles[2]] - V[opcodeNibbles[1]];
}

void Chip8::OP_8XYE()
{
    V[0xF] = (0x80u & V[opcodeNibbles[1]]) >> 0x7u;
    V[opcodeNibbles[1]] <<= 1;
}

void Chip8::OP_9XY0()
{
    if (V[opcodeNibbles[1]] != V[opcodeNibbles[2]])
    {
        pc += 2;
    }
}

void Chip8::OP_ANNN()
{
    I = opcodeNibbles[5];
}

void Chip8::OP_BNNN()
{
    pc = V[0x0] + opcodeNibbles[5];
}

void Chip8::OP_CXNN()
{
    V[opcodeNibbles[1]] = randInt(0, 254) & opcodeNibbles[4];
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

    for (uint row = 0; row < height; row++)
    {
        uint8_t spriteByte = memory[I + row];

        for (uint col = 0; col < 8; col++)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint8_t *screenPixel = &display[(xPos + col) + ((yPos + row) * 64)];

            if (spritePixel)
            {
                if (*screenPixel == 0xFFu)
                {
                    V[0xF] = 1;
                }

                *screenPixel ^= 0xFFu;
            }
        }
    }
    gfx->windowClear();
    gfx->drawPixels(&display);
    gfx->windowDisplay();
}

void Chip8::OP_EX9E()
{
    if (keypad[V[opcodeNibbles[1]]])
    {
        pc += 2;
    }
}

void Chip8::OP_EXA1()
{
    if (!keypad[V[opcodeNibbles[1]]])
    {
        pc += 2;
    }
}

void Chip8::OP_FX07()
{
    V[opcodeNibbles[1]] = delayTimer;
}

void Chip8::OP_FX0A()
{
    while (true)
    {
        if (keypad[0])
        {
            V[opcodeNibbles[1]] = 0;
            break;
        }
        else if (keypad[1])
        {
            V[opcodeNibbles[1]] = 1;
            break;
        }
        else if (keypad[2])
        {
            V[opcodeNibbles[1]] = 2;
            break;
        }
        else if (keypad[3])
        {
            V[opcodeNibbles[1]] = 3;
            break;
        }
        else if (keypad[4])
        {
            V[opcodeNibbles[1]] = 4;
            break;
        }
        else if (keypad[5])
        {
            V[opcodeNibbles[1]] = 5;
            break;
        }
        else if (keypad[6])
        {
            V[opcodeNibbles[1]] = 6;
            break;
        }
        else if (keypad[7])
        {
            V[opcodeNibbles[1]] = 7;
            break;
        }
        else if (keypad[8])
        {
            V[opcodeNibbles[1]] = 8;
            break;
        }
        else if (keypad[9])
        {
            V[opcodeNibbles[1]] = 9;
            break;
        }
        else if (keypad[10])
        {
            V[opcodeNibbles[1]] = 10;
            break;
        }
        else if (keypad[11])
        {
            V[opcodeNibbles[1]] = 11;
            break;
        }
        else if (keypad[12])
        {
            V[opcodeNibbles[1]] = 12;
            break;
        }
        else if (keypad[13])
        {
            V[opcodeNibbles[1]] = 13;
            break;
        }
        else if (keypad[14])
        {
            V[opcodeNibbles[1]] = 14;
            break;
        }
        else if (keypad[15])
        {
            V[opcodeNibbles[1]] = 15;
            break;
        }
    }
}

void Chip8::OP_FX15()
{
    delayTimer = V[opcodeNibbles[1]];
}

void Chip8::OP_FX18()
{
    soundTimer = V[opcodeNibbles[1]];
}

void Chip8::OP_FX1E()
{
    I += V[opcodeNibbles[1]];
}

void Chip8::OP_FX29()
{
    I = FONT_START_ADDRESS + (V[opcodeNibbles[1]] * 5);
}

void Chip8::OP_FX33() // Binary-coded decimal conversion
{
    uint8_t VX = V[opcodeNibbles[1]];
    uint8_t hundreds = 0;
    uint8_t tens = 0;
    uint8_t ones = 0;

    if (VX >= 100)
    {
        hundreds = (VX / 100);
        VX -= hundreds * 100;
    }

    if (VX >= 10)
    {
        tens = (VX / 10);
        VX -= tens * 10;
    }

    ones = VX;

    memory[I] = hundreds;
    memory[I + 1] = tens;
    memory[I + 2] = ones;
}

void Chip8::OP_FX55()
{
    for (uint X = 0; X <= opcodeNibbles[1]; X++)
    {
        memory[I + X] = V[X];
    }
}

void Chip8::OP_FX65()
{
    for (uint X = 0; X <= opcodeNibbles[1]; X++)
    {
        V[X] = memory[I + X];
    }
}

void Chip8::IMPLEMENTED()
{
    // std::cout << std::setfill('0') << std::setw(4) << std::right << std::hex << opcode;
    // std::cout << " IMPLEMENTED\n";
}

void Chip8::NOT_IMPLEMENTED()
{
    std::cout << std::setfill('0') << std::setw(4) << std::right << std::hex << opcode;
    std::cout << " NOT IMPLEMENTED\n";
}

uint8_t Chip8::randInt(int min, int max)
{
    uint8_t range = abs(min - max) + 1;
    uint8_t randNum = rand() % (range) + min;
    return randNum;
}