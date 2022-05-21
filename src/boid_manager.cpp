#include "boid_manager.h"


void BoidManager::init(unsigned initialQuantity) {

    numberOfBoids = 0;
    updateCount = 0;

    for (unsigned i = 0; i < initialQuantity; i++) {

        Boid boid;
        boid.init(WIN_SIZE_X/2.0f+i, WIN_SIZE_Y/2.0f+i, numberOfBoids++);
        boids.push_back(boid);
    }
}

void BoidManager::update() {

    std::vector<float> avgPos, avgVel;

    for (unsigned index = 0; index < numberOfBoids; index++) {

        avgPos.clear();
        avgVel.clear();

        bool canSeeOtherBoids = obtainAverages(avgPos, avgVel, boids[index]);

        if (canSeeOtherBoids) {

            boids[index].cohesion(avgPos);
            boids[index].alignment(avgVel);
            boids[index].separation(boids);

            boids[index].update();
        }
        else 
            boids[index].noDetection();
    }
}

void BoidManager::drawBoids(sf::RenderWindow &window) {

    for (unsigned index = 0; index < numberOfBoids; index++)
        boids[index].draw(window);

    std::vector<float> avgPos, avgVel;
    bool canSeeOtherBoids = obtainAverages(avgPos, avgVel, boids[0]);

    if (!canSeeOtherBoids) return;

    sf::CircleShape circle(BOID_SIZE);
    circle.setPosition(avgPos[0], avgPos[1]);
    circle.setFillColor(sf::Color::Red);

    window.draw(circle);
}

bool BoidManager::obtainAverages(std::vector<float> &avgPos, std::vector<float> &avgVel, 
                                 Boid currentBoid) {

    float sumX = 0, sumY = 0, sumVelX = 0, sumVelY = 0;

    bool canSeeOtherBoids = false;
    unsigned numberOfSeenBoids = 0;

    for (unsigned checkBoid = 0; checkBoid < numberOfBoids; checkBoid++) {
            
        float diffX = boids[checkBoid].posX() - currentBoid.posX(); 
        float diffY = boids[checkBoid].posY() - currentBoid.posY();

        float distance = sqrtf(powf(diffX, 2) + powf(diffY, 2));

        if (BOID_VISION_RADIUS > distance && currentBoid.identifier() != boids[checkBoid].identifier()) {

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