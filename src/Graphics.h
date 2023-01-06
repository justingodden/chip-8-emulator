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
    sf::CircleShape *circle = nullptr;
    sf::RectangleShape *pixel = nullptr;

public:
    void createWindow(std::string title);
    bool windowIsOpen();
    void windowClear();
    void drawCircle();
    void drawPixel(int xPos, int yPos);
    void windowDisplay();
    bool pollEvent(sf::Event &event);
    void close();

public:
    uint scaleFactor;

private:
    int randInt(int min, int max);
    uint width = 64;
    uint height = 32;
};

#endif