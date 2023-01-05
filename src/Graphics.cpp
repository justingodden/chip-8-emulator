#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Graphics.h"

Graphics::Graphics()
{
    window = new sf::RenderWindow;
}

Graphics::~Graphics()
{
    delete window;
}

void Graphics::createWindow(uint x, uint y, std::string title)
{
    window->create(sf::VideoMode(x, y), title);
}

bool Graphics::windowIsOpen()
{
    return window->isOpen();
}

void Graphics::windowClear()
{
    window->clear();
}

void Graphics::drawCircle()
{
    int radius = randInt(25, 100);
    sf::CircleShape shape(radius);
    int x = randInt(-radius, window->getSize().x);
    int y = randInt(-radius, window->getSize().y);
    float xF = static_cast<float>(x);
    float yF = static_cast<float>(y);
    shape.setPosition(xF, yF);
    shape.setFillColor(sf::Color(
        randInt(0, 255),
        randInt(0, 255),
        randInt(0, 255)));
    window->draw(shape);
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