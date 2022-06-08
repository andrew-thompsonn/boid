#ifndef _BOID_MANAGER_H_
#define _BOID_MANAGER_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "boid.h"
#include "window_properties.h"

class BoidManager {

    /* Buffer of boids */
    std::vector <Boid> boids;

    /* Buffer of 'predator' boids */
    std::vector <Boid> hostileBoids;

    /* Size of buffers */
    unsigned numberOfBoids;
    unsigned numberOfHostileBoids;

    /* Debounce for predator spawn */
    unsigned coolDown;

    /**
     * @brief Get the average velocity and position of all visibile boids relative to the currentBoid.
     * 
     * @param avgPos        Buffer for average position relative to current boid
     * @param avgVel        Buffer for average velocity relative to current boid 
     * @param currentBoid   Current boid object
     * @return true 
     * @return false 
     */
    bool obtainAverages(std::vector<float> &avgPos, std::vector<float> &avgVel, 
                        Boid currentBoid);
public: 
    /**
     * @brief Initialize all boids. 
     * 
     * @param initialQuanitity      The number of boids to be created
     */
    void init(unsigned initialQuanitity);

    /**
     * @brief Update all the boids. 
     */
    void update();

    /**
     * @brief Draw all boids.
     * 
     * @param window        The SFML render window to draw the boids on.
     */
    void drawBoids(sf::RenderWindow &window);

    /**
     * @brief Add a hostile boid to the simulation.
     */
    void addHostile();
};
#endif /* _BOID_MANAGER_H_ */