#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Graphics.h"

Graphics::Graphics()
{
    window = new sf::RenderWindow;
    circle = new sf::CircleShape;
}

Graphics::~Graphics()
{
    delete window;
    delete circle;
}

void Graphics::createWindow(uint width, uint height, std::string title)
{
    window->create(sf::VideoMode(width, height), title);
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
    circle->setRadius(radius);
    int x = randInt(-radius, window->getSize().x);
    int y = randInt(-radius, window->getSize().y);
    float xF = static_cast<float>(x);
    float yF = static_cast<float>(y);
    circle->setPosition(xF, yF);
    circle->setFillColor(sf::Color(
        randInt(0, 255),
        randInt(0, 255),
        randInt(0, 255)));
    window->draw(*circle);
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