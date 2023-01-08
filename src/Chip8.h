#ifndef CHIP8_CPP_CHIP8_H
#define CHIP8_CPP_CHIP8_H

#include <stdint.h>
#include <array>
#include <stack>
#include "Graphics.h"

class Chip8
{
public:
    Chip8(std::string romPath);
    ~Chip8();

public:
    void loop();

private:
    void loadROM();
    void LoadFonts();
    void fetch();
    void decodeExecute();

private:
    Graphics *gfx = nullptr;
    uint16_t PC_START_ADDRESS = 0x200;
    uint16_t FONT_START_ADDRESS = 0x50;
    uint16_t opcode;
    std::array<uint16_t, 6> opcodeNibbles;
    std::string romPath;
    int clockDelay = 1;

    std::array<uint8_t, 16> V; // registers V0,... VF
    uint16_t I;
    uint16_t pc = PC_START_ADDRESS;
    std::array<uint8_t, 4096> memory;
    std::array<uint8_t, 64 * 32> display;
    std::stack<uint16_t> stack;
    uint8_t delayTimer;
    uint8_t soundTimer;
    std::array<uint8_t, 16> keypad;

    std::array<uint8_t, 5 * 16> fontData = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

private:
    void OP_0NNN();
    void OP_00E0();
    void OP_00EE();

    void OP_1NNN();
    void OP_2NNN();
    void OP_3XNN();
    void OP_4XNN();
    void OP_5XY0();
    void OP_6XNN();
    void OP_7XNN();

    void OP_8XY0();
    void OP_8XY1();
    void OP_8XY2();
    void OP_8XY3();
    void OP_8XY4();
    void OP_8XY5();
    void OP_8XY6();
    void OP_8XY7();
    void OP_8XYE();

    void OP_9XY0();
    void OP_ANNN();
    void OP_BNNN();
    void OP_CXNN();
    void OP_DXYN();

    void OP_EX9E();
    void OP_EXA1();

    void OP_FX07();
    void OP_FX0A();
    void OP_FX15();
    void OP_FX18();
    void OP_FX1E();
    void OP_FX29();
    void OP_FX33();
    void OP_FX55();
    void OP_FX65();

    void IMPLEMENTED();
    void NOT_IMPLEMENTED();

    uint8_t randInt(int min, int max);
};

#endif