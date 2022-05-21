#include "boid.h"

void Boid::init(float positionXIn, float positionYIn, unsigned idIn) {

    position.push_back(positionXIn);
    position.push_back(positionYIn);

    velocity.push_back(0.0f);
    velocity.push_back(0.0f);

    cohesionVector.push_back(0.0f);
    cohesionVector.push_back(0.0f);

    alignmentVector.push_back(0.0f);
    alignmentVector.push_back(0.0f);

    separationVector.push_back(0.0f);
    separationVector.push_back(0.0f);

    id = idIn;

    initComplete = false;
}

void Boid::update() {

    if (!initComplete) {
        velocity[0] = 10.0f*BOID_SPEED;
        velocity[1] = 0.0f;
        initComplete = true;
        position[0] += velocity[0];
        position[1] += velocity[1];
        return;
    }

    normalizeVector(cohesionVector);
    normalizeVector(alignmentVector);
    normalizeVector(separationVector);

    velocity[0] = 0.0f;
    velocity[1] = 0.0f;

    sumVelocities();
    normalizeVector(velocity);

    position[0] += velocity[0];
    position[1] += velocity[1];

    if (position[0] < 0)            position[0] = WIN_SIZE_X;
    if (position[0] > WIN_SIZE_X)   position[0] = 0.0f;

    if (position[1] < 0)            position[1] = WIN_SIZE_Y;
    if (position[1] > WIN_SIZE_Y)   position[1] = 0.0f;
}

void Boid::draw(sf::RenderWindow &window) {

    sf::CircleShape circle(10);
    circle.setPosition(position[0], position[1]);

    window.draw(circle);
}

void Boid::cohesion(std::vector<float> centerOfMass) {

    cohesionVector[0] = (centerOfMass[0] - position[0]);
    cohesionVector[1] = (centerOfMass[1] - position[1]);
}

void Boid::alignment(std::vector<float> direction) {

    alignmentVector[0] = (direction[0] - velocity[0]);
    alignmentVector[1] = (direction[1] - velocity[1]);
}

void Boid::separation(std::vector<Boid> boids) {

    separationVector[0] = 0.0f;
    separationVector[1] = 0.0f;

    for (unsigned index = 0; index < boids.size(); index++) {
        if (id != boids[index].identifier()) { 
            
            float diffX = boids[index].posX() - position[0];
            float diffY = boids[index].posY() - position[1];

            float distance = sqrtf(powf(diffX, 2) + powf(diffY, 2));

            if (BOID_SEPARATION > distance) {
                separationVector[0] -= diffX;
                separationVector[1] -= diffY;
            }
        }
    }
}

void Boid::sumVelocities() {

    velocity[0] = cohesionVector[0] + alignmentVector[0] + SEPARATION_WEIGHT*separationVector[0];
    velocity[1] = cohesionVector[1] + alignmentVector[1] + SEPARATION_WEIGHT*separationVector[1];
}

void Boid::normalizeVector(std::vector<float> &vec) {

    if (sqrtf(powf(vec[0], 2.0f) + powf(vec[1], 2.0f)) < 0.00001f) return;

    float speed = sqrtf( powf(vec[0], 2.0f) + powf(vec[1], 2.0f) );

    vec[0] = BOID_SPEED*vec[0]/speed;
    vec[1] = BOID_SPEED*vec[1]/speed;
}

float Boid::posX() { return position[0]; }

float Boid::posY() { return position[1]; }

float Boid::velX() { return velocity[0]; }

float Boid::velY() { return velocity[1]; }

unsigned Boid::identifier() { return id; }