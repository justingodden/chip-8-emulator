#include <array>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Graphics.h"

Graphics::Graphics(uint scaleFactor)
    : scaleFactor(scaleFactor)
{
    window = new sf::RenderWindow;
    texture = new sf::Texture;
    sprite = new sf::Sprite;
    texture->create(64, 32);
}

Graphics::~Graphics()
{
    delete window;
    delete texture;
    delete sprite;
    delete pixels;
}

void Graphics::createWindow(std::string title)
{
    window->create(sf::VideoMode(width * scaleFactor, height * scaleFactor), title);
}

bool Graphics::windowIsOpen()
{
    return window->isOpen();
}

void Graphics::windowClear()
{
    window->clear();
}

void Graphics::drawPixels(std::array<uint8_t, 64 * 32> *display)
{
    for (uint i = 0; i < 64 * 32; i++)
    {
        pixels[i * 4] = (*display)[i];
        pixels[(i * 4) + 1] = (*display)[i];
        pixels[(i * 4) + 2] = (*display)[i];
        pixels[(i * 4) + 3] = (*display)[i];
    }

    texture->update(pixels);
    sprite->setTexture(*texture);
    sprite->setScale(scaleFactor, scaleFactor);
    window->draw(*sprite);
}

void Graphics::windowDisplay()
{
    window->display();
}

bool Graphics::pollEvent(sf::Event &event)
{
    return window->pollEvent(event);
}

void Graphics::close()
{
    window->close();
}

int Graphics::randInt(int min, int max)
{
    int range = abs(min - max) + 1;
    int randNum = rand() % (range) + min;
    return randNum;
}