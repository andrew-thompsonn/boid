#ifndef _BOID_MANAGER_H_
#define _BOID_MANAGER_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "boid.h"
#include "window_properties.h"

#include <stdio.h>

class BoidManager {

    std::vector <Boid> boids;

    unsigned numberOfBoids;

    void coherence(); // Fly towards center of mass

    void separation(); // Maintain some distance of separation 

    void alignment(); // Fly in similar direction

    void obtainAverages(std::vector<float> &avgPos, std::vector<float> &avgVel);

public: 

    void init(unsigned initialQuanitity);

    void update();

    void drawBoids(sf::RenderWindow &window);

    void placeBoid(float positionX, float poisitionY);

};


#endif /* _BOID_MANAGER_H_ */