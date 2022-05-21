#include "boid_manager.h"


void BoidManager::init(unsigned initialQuantity) {

    numberOfBoids = 0;

    for (unsigned index = 0; index < initialQuantity; index++) {

        float positionX = ((rand() % 100) / 100.0f)*WIN_SIZE_X;
        float positionY = ((rand() % 100) / 100.0f)*WIN_SIZE_Y;

        Boid boid;
        boid.init(positionX, positionY, numberOfBoids++);

        boids.push_back(boid);
    }
}

void BoidManager::update() {

    std::vector<float> avgPos, avgVel;
    obtainAverages(avgPos, avgVel);

    for (unsigned index = 0; index < numberOfBoids; index++) {

        boids[index].cohesion(avgPos);
        boids[index].alignment(avgVel);
        boids[index].separation(boids);
        boids[index].update();
    }
}

void BoidManager::drawBoids(sf::RenderWindow &window) {

    for (unsigned index = 0; index < numberOfBoids; index++)
        boids[index].draw(window);
}

void BoidManager::obtainAverages(std::vector<float> &avgPos, std::vector<float> &avgVel) {

    float sumX = 0, sumY = 0, sumVelX = 0, sumVelY = 0;

    for (unsigned index = 0; index < numberOfBoids; index++) {

        sumX += boids[index].posX();
        sumY += boids[index].posY();

        sumVelX += boids[index].velX();
        sumVelY += boids[index].velY();
    }
    avgPos.push_back(sumX/numberOfBoids);
    avgPos.push_back(sumY/numberOfBoids);

    avgVel.push_back(sumVelX/numberOfBoids);
    avgVel.push_back(sumVelY/numberOfBoids);
}