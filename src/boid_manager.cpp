#include "boid_manager.h"


void BoidManager::init(unsigned initialQuantity) {

    numberOfBoids = 0;
    updateCount = 0;

    for (unsigned i = 0; i < initialQuantity; i++) {

        /* Random position within the size of the window */
        float posX = ((rand() % 100)/100.0f)*WIN_SIZE_X;
        float posY = ((rand() % 100)/100.0f)*WIN_SIZE_Y;

        Boid boid;
        boid.init(posX, posY, numberOfBoids++, boidSpecies_t::FRIENDLY);

        boids.push_back(boid);
    }
}

void BoidManager::update() {

    std::vector<float> avgPos, avgVel;

    for (unsigned index = 0; index < boids.size(); index++) {

        avgPos.clear();
        avgVel.clear();

        bool canSeeOtherBoids = obtainAverages(avgPos, avgVel, boids[index]);
        
        boids[index].survive(hostileBoids);

        if (canSeeOtherBoids) {

            boids[index].cohesion(avgPos);
            boids[index].alignment(avgVel);
            boids[index].separation(boids);
            boids[index].update();
        }
        else
            boids[index].noDetection();
    }
    for (unsigned index = 0; index < hostileBoids.size(); index++) {

        avgPos.clear();
        avgVel.clear();

        bool canSeeOtherBoids = obtainAverages(avgPos, avgVel, hostileBoids[index]);

        if (canSeeOtherBoids) {

            hostileBoids[index].cohesion(avgPos);
            hostileBoids[index].separation(hostileBoids);
            hostileBoids[index].update();
        }
        else 
            hostileBoids[index].noDetection();
    }
}

void BoidManager::drawBoids(sf::RenderWindow &window) {

    for (unsigned index = 0; index < boids.size(); index++)
        boids[index].draw(window);

    for (unsigned index = 0; index < hostileBoids.size(); index++)
        hostileBoids[index].draw(window);
}

bool BoidManager::obtainAverages(std::vector<float> &avgPos, std::vector<float> &avgVel, 
                                 Boid currentBoid) {

    float sumX = 0, sumY = 0, sumVelX = 0, sumVelY = 0;

    bool canSeeOtherBoids = false;
    unsigned numberOfSeenBoids = 0;

    float radius = currentBoid.getSpecies() == boidSpecies_t::HOSTILE ? HOSTILE_BOID_RADIUS : BOID_VISION_RADIUS;

    for (unsigned checkBoid = 0; checkBoid < boids.size(); checkBoid++) {

        if (currentBoid.identifier() == boids[checkBoid].identifier())
            continue;
            
        float diffX = boids[checkBoid].posX() - currentBoid.posX(); 
        float diffY = boids[checkBoid].posY() - currentBoid.posY();

        float distance = sqrtf(powf(diffX, 2) + powf(diffY, 2));
        float dot = diffX*currentBoid.velX() + diffY*currentBoid.velY();

        if (currentBoid.getSpecies() == boidSpecies_t::HOSTILE)
            dot = 1.0f;

        if (radius > distance && dot > -0.45f) {

            canSeeOtherBoids = true;

            sumX += boids[checkBoid].posX();
            sumY += boids[checkBoid].posY();

            sumVelX += boids[checkBoid].velX();
            sumVelY += boids[checkBoid].velY();

            numberOfSeenBoids++;
        }
    }
    if (canSeeOtherBoids) {

        avgPos.push_back(sumX/numberOfSeenBoids);
        avgPos.push_back(sumY/numberOfSeenBoids);

        avgVel.push_back(sumVelX/numberOfSeenBoids);
        avgVel.push_back(sumVelY/numberOfSeenBoids);

        return true;
    }
    return false;
}

void BoidManager::addHostile() {
        
    float posX = ((rand() % 100)/100.0f)*WIN_SIZE_X;
    float posY = ((rand() % 100)/100.0f)*WIN_SIZE_Y;

    Boid boid;
    boid.init(posX, posY, numberOfBoids++, boidSpecies_t::HOSTILE);

    hostileBoids.push_back(boid);
    printf("Added hostile. %d hostiles\n", hostileBoids.size());
}