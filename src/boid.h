#ifndef _BOID_H_
#define _BOID_H_

#include <SFML/Graphics.hpp>

class Boid {

    float positionX;

    float positionY;

    float directionFromNorth;

public:

    void init(float positionXin, float positionYin);

    void update();

    void draw(sf::RenderWindow &window);
};

#endif /* _BOID_H_ */