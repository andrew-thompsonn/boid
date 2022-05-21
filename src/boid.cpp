#include "boid.h"

void Boid::init(float positionXIn, float positionYIn, unsigned idIn) {

    position.push_back(positionXIn);
    position.push_back(positionYIn);

    velocity.push_back(0);
    velocity.push_back(0);

    cohesionVector.push_back(0.0f);
    cohesionVector.push_back(0.0f);

    alignmentVector.push_back(0.0f);
    alignmentVector.push_back(0.0f);

    separationVector.push_back(0.0f);
    separationVector.push_back(0.0f);

    id = idIn;
    updateCounter = 0;
}

void Boid::update() {

    sumVelocities();

    float speed = sqrtf(powf(velocity[0], 2) + powf(velocity[1], 2));
    normalizeVector(velocity, MAX_SPEED);

    position[0] += velocity[0]; 
    position[1] += velocity[1];

    if (position[0] < 0)            position[0] = WIN_SIZE_X; 
    if (position[0] > WIN_SIZE_X)   position[0] = 0;

    if (position[1] < 0)            position[1] = WIN_SIZE_Y;
    if (position[1] > WIN_SIZE_Y)   position[1] = 0;
}

void Boid::draw(sf::RenderWindow &window) {

    sf::CircleShape circle(BOID_SIZE);
    circle.setPosition(position[0], position[1]);
    circle.setFillColor(sf::Color::Black);

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

    velocity[0] += COHESION_WEIGHT*cohesionVector[0] + 
                   ALIGNMENT_WEIGHT*alignmentVector[0] + 
                   SEPARATION_WEIGHT*separationVector[0];

    velocity[1] += COHESION_WEIGHT*cohesionVector[1] + 
                   ALIGNMENT_WEIGHT*alignmentVector[1] + 
                   SEPARATION_WEIGHT*separationVector[1];
}

void Boid::normalizeVector(std::vector<float> &vec, float scale) {

    if (sqrtf(powf(vec[0], 2.0f) + powf(vec[1], 2.0f)) < 0.00001f) return;

    float speed = sqrtf( powf(vec[0], 2.0f) + powf(vec[1], 2.0f) );

    vec[0] = scale*vec[0]/speed;
    vec[1] = scale*vec[1]/speed;
}

void Boid::noDetection() {

    float direction = (rand() % 360) * PI/180.0f;

    velocity[0] += BOID_SPEED*sinf(direction);
    velocity[1] += BOID_SPEED*cosf(direction);

    float speed = sqrtf(powf(velocity[0], 2) + powf(velocity[1], 2));
    if (speed > MAX_SPEED)
        normalizeVector(velocity, MAX_SPEED);

    position[0] += velocity[0];    
    position[1] += velocity[1];

    if (position[0] < 0)            position[0] = WIN_SIZE_X;
    if (position[0] > WIN_SIZE_X)   position[0] = 0.0f;

    if (position[1] < 0)            position[1] = WIN_SIZE_Y;
    if (position[1] > WIN_SIZE_Y)   position[1] = 0.0f;
}

float Boid::posX() { return position[0]; }

float Boid::posY() { return position[1]; }

float Boid::velX() { return velocity[0]; }

float Boid::velY() { return velocity[1]; }

unsigned Boid::identifier() { return id; }