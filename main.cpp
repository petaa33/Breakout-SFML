#include <SFML/Graphics.hpp>
#include "game.h"
#include "iostream"

int main()
{
	Game game;

    while (game.window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = game.window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                game.window.close();
            }

        }
	    game.run();
    }
}