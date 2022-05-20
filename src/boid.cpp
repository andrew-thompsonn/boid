#include "boid.h"

void Boid::init(float positionXIn, float positionYIn) {

    positionX = positionXIn;
    positionY = positionYIn;
}

void Boid::update() {

    
}

void Boid::draw(sf::RenderWindow &window) {

    sf::CircleShape triangle(80, 3);

    triangle.setPosition(200, 200);
    window.draw(triangle);
}
