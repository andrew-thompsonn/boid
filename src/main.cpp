#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "window_properties.h"
#include "boid_manager.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y),
                            WIN_TITLE, sf::Style::Close);
    BoidManager manager;
    manager.init(120);

    sf::Clock timer;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                continue;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                manager.addHostile();
        }
        window.clear(sf::Color(0, 38, 64));

        manager.update();
        manager.drawBoids(window);

        window.display();
    }
    return EXIT_SUCCESS;
}
 