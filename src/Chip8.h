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

    void NOT_IMPLEMENTED();

private:
    Graphics *gfx = nullptr;
    uint16_t PC_START_ADDRESS = 0x200;
    uint16_t FONT_START_ADDRESS = 0x50;
    uint16_t opcode;
    std::array<uint8_t, 6> opcodeNibbles;
    std::string romPath;
    int clockDelay = 1;

    std::array<uint8_t, 16> V; // registers V0,... VF
    uint16_t I;
    uint16_t pc;
    std::array<uint8_t, 4096> memory;
    std::array<uint8_t, 64 * 32> display;
    std::stack<uint16_t> stack;
    uint16_t sp;
    uint8_t delayTimer;
    uint8_t soundTimer;
    std::array<uint8_t, 16> keypad;

    std::map<uint16_t, void (Chip8::*)()> functionMap;

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
    void OP_00E0();
    void OP_1NNN();
    void OP_6XNN();
    void OP_7XNN();
    void OP_ANNN();
    void OP_DXYN();
};

#endif