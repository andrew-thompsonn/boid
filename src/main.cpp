#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

#include "window_properties.h"
#include "boid.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y),
                            WIN_TITLE, sf::Style::Close);
    window.setVerticalSyncEnabled (true);

    Boid boid;
    boid.init(200, 200);

    sf::Clock timer;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                continue;
            }
        }
        window.clear( sf::Color::Black);
        boid.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}

 