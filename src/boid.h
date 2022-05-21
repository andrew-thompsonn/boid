#ifndef _BOID_H_
#define _BOID_H_

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "window_properties.h"

#define BOID_SPEED          (5)
#define BOID_SEPARATION     (60)

#define BOID_VISION_RADIUS  (100)

#define SEPARATION_WEIGHT   (3)

class Boid {

    std::vector<float> position;
    std::vector<float> velocity;

    std::vector<float> cohesionVector;
    std::vector<float> alignmentVector;
    std::vector<float> separationVector;

    void sumVelocities();
    void normalizeVector(std::vector<float> &vec);

    unsigned id;

    bool initComplete;

public:
    
    void cohesion(std::vector<float> centerOfMass);
    void alignment(std::vector<float> direction);
    void separation(std::vector<Boid> boids);

    float posX();
    float posY();
    float velX();
    float velY();

    unsigned identifier();
    
    void update();
    void init(float positionXin, float positionYin, unsigned id);
    void draw(sf::RenderWindow &window);
};
#endif /* _BOID_H_ */