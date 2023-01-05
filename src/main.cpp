#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Graphics.h"

int main()
{
    uint w = 500;
    uint h = 500;
    std::string title = "Chip8 Emulator";

    Graphics gfx;
    gfx.createWindow(w, h, title);

    while (gfx.windowIsOpen())
    {
        sf::Event event;
        while (gfx.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gfx.close();
        }
        gfx.windowClear();
        gfx.drawCircle();
        gfx.windowDisplay();

        sf::Time t = sf::milliseconds(100);
        sf::sleep(t);
    }

    return 0;
}