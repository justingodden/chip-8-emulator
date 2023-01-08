#ifndef CHIP8_CPP_GRAPHICS_H
#define CHIP8_CPP_GRAPHICS_H

#include <string.h>
#include <SFML/Graphics.hpp>

class Graphics
{
public:
    Graphics(uint scaleFactor);
    ~Graphics();

private:
    sf::RenderWindow *window = nullptr;
    sf::Texture *texture = nullptr;
    sf::Sprite *sprite = nullptr;
    sf::Uint8 *pixels = new sf::Uint8[64 * 32 * 4];

public:
    void createWindow(std::string title);
    bool windowIsOpen();
    void windowClear();
    void drawPixels(std::array<uint8_t, 64 * 32> *display);
    void windowDisplay();
    bool pollEvent(sf::Event &event);
    bool checkKeyPresses(std::array<uint8_t, 16> &keypad);
    void close();

public:
    uint scaleFactor;

private:
    uint width = 64;
    uint height = 32;
};

#endif