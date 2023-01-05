#ifndef CHIP8_CPP_GRAPHICS_H
#define CHIP8_CPP_GRAPHICS_H

#include <string.h>
#include <SFML/Graphics.hpp>

class Graphics
{
public:
    Graphics();
    ~Graphics();

private:
    sf::RenderWindow *window = nullptr;

public:
    void createWindow(uint x, uint y, std::string title);
    bool windowIsOpen();
    void windowClear();
    void drawCircle();
    void windowDisplay();
    bool pollEvent(sf::Event &event);
    void close();

private:
    int randInt(int min, int max);
};

#endif