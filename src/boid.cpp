#include "boid.h"

void Boid::init(float positionXIn, float positionYIn, unsigned idIn, boidSpecies_t speciesIn) {

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

    survivalVector.push_back(0.0f);
    survivalVector.push_back(0.0f);

    id = idIn;
    updateCounter = 0;

    species = speciesIn;
    surviving = false;
    survivalCounter = 0;
}

void Boid::update() {
    
    sumVelocities();

    if (species == boidSpecies_t::FRIENDLY && survivalCounter > 0) {
        normalizeVector(velocity, 2.0f*MAX_SPEED);
        surviving = true;
        survivalCounter--;
    }
    else if (species == boidSpecies_t::HOSTILE) {
        normalizeVector(velocity, 1.25f*MAX_SPEED);
    }
    else {
        normalizeVector(velocity, MAX_SPEED);
        surviving = false;
    }

    position[0] += velocity[0]; 
    position[1] += velocity[1];

    if (position[0] < 0)            position[0] = WIN_SIZE_X; 
    if (position[0] > WIN_SIZE_X)   position[0] = 0;

    if (position[1] < 0)            position[1] = WIN_SIZE_Y;
    if (position[1] > WIN_SIZE_Y)   position[1] = 0;
}

void Boid::draw(sf::RenderWindow &window) {

    sf::Color color;
    if (boidSpecies_t::FRIENDLY == species) 
        color = surviving ? sf::Color::Magenta : sf::Color(0, 255, 112);
    else 
        color = sf::Color(255, 21, 21);


    sf::CircleShape boid(BOID_SIZE);
    boid.setPosition(position[0], position[1]);
    boid.setFillColor(color);

    float direction = atan2f(velocity[0], velocity[1]);
    
    sf::Vertex tail[]{
        sf::Vertex(sf::Vector2f(position[0] + BOID_SIZE, position[1] + BOID_SIZE), color),
        sf::Vertex(sf::Vector2f(position[0] + BOID_SIZE - 4*BOID_SIZE*sinf(direction), 
                                position[1] + BOID_SIZE - 4*BOID_SIZE*cosf(direction)), color)
    };
    window.draw(boid);
    window.draw(tail, 2, sf::Lines);
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

    float separation = species == boidSpecies_t::HOSTILE ? 5.0f*BOID_SEPARATION : BOID_SEPARATION;

    for (unsigned index = 0; index < boids.size(); index++) {
        if (id != boids[index].identifier()) { 
            
            float diffX = boids[index].posX() - position[0];
            float diffY = boids[index].posY() - position[1];

            float distance = sqrtf(powf(diffX, 2) + powf(diffY, 2));

            if (separation > distance) {
                separationVector[0] -= diffX;
                separationVector[1] -= diffY;
            }
        }
    }
}

void Boid::survive(std::vector<Boid> hostileBoids) {

    survivalVector[0] = 0.0f;
    survivalVector[1] = 0.0f;

    surviving = false;

    for (unsigned index = 0; index < hostileBoids.size(); index++) {

        float diffX = hostileBoids[index].posX() - position[0];
        float diffY = hostileBoids[index].posY() - position[1];

        float distance = sqrtf(powf(diffX, 2) + powf(diffY, 2));

        if (4.0f*BOID_SEPARATION > distance) {
            survivalVector[0] -= diffX;
            survivalVector[1] -= diffY;
            surviving = true; 
        }
    }
    if (surviving) survivalCounter = 6;
}

void Boid::sumVelocities() {
    
    if (species == boidSpecies_t::FRIENDLY && surviving) {
        
        velocity[0] += SURVIVAL_WEIGHT*survivalVector[0];
        velocity[1] += SURVIVAL_WEIGHT*survivalVector[1];
    }
        
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

    /* Random anlge between 0 and 180 degrees */
    float direction = (rand() % 360) * PI/180.0f;

    velocity[0] += sinf(direction);
    velocity[1] += cosf(direction);

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

bool Boid::canSee(Boid otherBoid, float radius) {

    if (otherBoid.identifier() == id)
        return false;

    float diffX = otherBoid.posX() - position[0];
    float diffY = otherBoid.posY() - position[1];

    float distance = sqrtf(powf(diffX, 2) + powf(diffY, 2));
    float dot = diffX*velocity[0] + diffY*velocity[1];

    if (radius > distance && dot > 0) 
        return true;

    return false;
}

float Boid::posX() { return position[0]; }

float Boid::posY() { return position[1]; }

float Boid::velX() { return velocity[0]; }

float Boid::velY() { return velocity[1]; }

unsigned Boid::identifier() { return id; }

boidSpecies_t Boid::getSpecies() { return species; }