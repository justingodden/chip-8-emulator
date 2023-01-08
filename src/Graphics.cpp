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

bool Graphics::checkKeyPresses(std::array<uint8_t, 16> &keypad)
{
    bool running = true;

    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            running = false;
            return running;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window->close();
                running = false;
                return running;

            case sf::Keyboard::Num1:
                keypad[0x0] = 1;
                return running;
            case sf::Keyboard::Num2:
                keypad[0x1] = 1;
                return running;
            case sf::Keyboard::Num3:
                keypad[0x2] = 1;
                return running;
            case sf::Keyboard::Num4:
                keypad[0x3] = 1;
                return running;
            case sf::Keyboard::Q:
                keypad[0x4] = 1;
                return running;
            case sf::Keyboard::W:
                keypad[0x5] = 1;
                return running;
            case sf::Keyboard::E:
                keypad[0x6] = 1;
                return running;
            case sf::Keyboard::R:
                keypad[0x7] = 1;
                return running;
            case sf::Keyboard::A:
                keypad[0x8] = 1;
                return running;
            case sf::Keyboard::S:
                keypad[0x9] = 1;
                return running;
            case sf::Keyboard::D:
                keypad[0xA] = 1;
                return running;
            case sf::Keyboard::F:
                keypad[0xB] = 1;
                return running;
            case sf::Keyboard::Z:
                keypad[0xC] = 1;
                return running;
            case sf::Keyboard::X:
                keypad[0xD] = 1;
                return running;
            case sf::Keyboard::C:
                keypad[0xE] = 1;
                return running;
            case sf::Keyboard::V:
                keypad[0xF] = 1;
                return running;
            default:
                return running;
            }

        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Num1:
                keypad[0x0] = 0;
                return running;
            case sf::Keyboard::Num2:
                keypad[0x1] = 0;
                return running;
            case sf::Keyboard::Num3:
                keypad[0x2] = 0;
                return running;
            case sf::Keyboard::Num4:
                keypad[0x3] = 0;
                return running;
            case sf::Keyboard::Q:
                keypad[0x4] = 0;
                return running;
            case sf::Keyboard::W:
                keypad[0x5] = 0;
                return running;
            case sf::Keyboard::E:
                keypad[0x6] = 0;
                return running;
            case sf::Keyboard::R:
                keypad[0x7] = 0;
                return running;
            case sf::Keyboard::A:
                keypad[0x8] = 0;
                return running;
            case sf::Keyboard::S:
                keypad[0x9] = 0;
                return running;
            case sf::Keyboard::D:
                keypad[0xA] = 0;
                return running;
            case sf::Keyboard::F:
                keypad[0xB] = 0;
                return running;
            case sf::Keyboard::Z:
                keypad[0xC] = 0;
                return running;
            case sf::Keyboard::X:
                keypad[0xD] = 0;
                return running;
            case sf::Keyboard::C:
                keypad[0xE] = 0;
                return running;
            case sf::Keyboard::V:
                keypad[0xF] = 0;
                return running;
            default:
                return running;
            }
        default:
            return running;
        }
    }

    return running;
}

void Graphics::close()
{
    window->close();
}