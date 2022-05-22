#ifndef _BOID_H_
#define _BOID_H_

#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "window_properties.h"

#define HOSTILE_SPEED       (3.5f)
#define MAX_SPEED           (6.0f)
#define BOID_SEPARATION     (10.0f)
#define BOID_VISION_RADIUS  (80.0f)
#define BOID_SIZE           (5)

#define HOSTILE_BOID_RADIUS (350.0f)

#define ALIGNMENT_WEIGHT    (0.125f)
#define SEPARATION_WEIGHT   (0.5f)
#define COHESION_WEIGHT     (0.010f)
#define SURVIVAL_WEIGHT     (1.0f)

#define PI                  (3.14159)

typedef enum {

    FRIENDLY,
    HOSTILE

} boidSpecies_t;

class Boid {

    std::vector<float> position;
    std::vector<float> velocity;

    std::vector<float> cohesionVector;
    std::vector<float> alignmentVector;
    std::vector<float> separationVector;
    std::vector<float> survivalVector;

    void sumVelocities();
    void normalizeVector(std::vector<float> &vec, float scale);
    void averageVelocity();

    unsigned id;
    unsigned long updateCounter;
    float targetX, targetY;

    bool surviving;

    unsigned short survivalCounter;

    boidSpecies_t species;

public:

    void cohesion(std::vector<float> centerOfMass);
    void alignment(std::vector<float> direction);
    void separation(std::vector<Boid> boids);
    void survive(std::vector<Boid> hostileBoids);

    void noDetection();
    bool canSee(Boid otherBoid);

    float posX(), posY(), velX(), velY();
    unsigned identifier();
    boidSpecies_t getSpecies();
 
    void update();
    void init(float positionXin, float positionYin, unsigned id, boidSpecies_t speciesIn);
    void draw(sf::RenderWindow &window);
};
#endif /* _BOID_H_ */