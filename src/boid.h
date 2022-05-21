#ifndef _BOID_H_
#define _BOID_H_

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "window_properties.h"

#define BOID_SPEED          (3.5f)
#define MAX_SPEED           (6.0f)
#define BOID_SEPARATION     (20.0f)
#define BOID_VISION_RADIUS  (60.0f)
#define BOID_SIZE           (5)

#define ALIGNMENT_WEIGHT    (0.35f)
#define SEPARATION_WEIGHT   (3.0f)
#define COHESION_WEIGHT     (0.080f)

#define PI                  (3.14159)

class Boid {

    std::vector<float> position;
    std::vector<float> velocity;

    std::vector<float> cohesionVector;
    std::vector<float> alignmentVector;
    std::vector<float> separationVector;

    void sumVelocities();
    void normalizeVector(std::vector<float> &vec, float scale);
    void averageVelocity();

    unsigned id;
    unsigned long updateCounter;
    float targetX, targetY;

public:

    void cohesion(std::vector<float> centerOfMass);
    void alignment(std::vector<float> direction);
    void separation(std::vector<Boid> boids);

    void noDetection();

    float posX(), posY(), velX(), velY();
    unsigned identifier();
 
    void update();
    void init(float positionXin, float positionYin, unsigned id);
    void draw(sf::RenderWindow &window);
};
#endif /* _BOID_H_ */