#ifndef CITY_H
#define CITY_H
#include "Organism.h"

// The possible moves
enum Move {UP = 0, DOWN, LEFT, RIGHT};

// Config Values
const int CITYSIZE = 20; // Row and Column size of city
const int HUMAN_STARTCOUNT = 100;
const int ZOMBIE_STARTCOUNT = 5;
const int HUMAN_BREEDCOUNT = 3;
const int ZOMBIE_BREEDCOUNT = 8;
const int ZOMBIE_STARVECOUNT = 3;

struct Position
{
    int x;
    int y;
};

class City
{
public:
    City(unsigned int seed); // Constructor: creates and initializes this city.
    ~City(); // Destructor.
    Organism* getOrganism(int x, int y) const; // Returns the organism at the given coordinates.
    void setOrganism(int x, int y, Organism *org); // Sets the organism org at position (x,y).
    void displayCity() const; // Displays the city.
    void step(); // Simulates one time step.
    bool isExtinct(); // Checks if extinction event has occurred
    Position randomPosition() const; // Returns a random position in the grid.
    Move randomMove() const; // Returns a random move

private:
    Organism* grid[CITYSIZE][CITYSIZE]; // The grid
    void createOrganisms(OrganismType orgType, int count); // Randomly create a number of an organism
    void resetOrganisms(); // Reset all organisms to not moved.
    void moveOrganism(OrganismType aType); // Make every organism in the city of this type move.
    void cleanup(); // Remove all dead/starved organism from the city.
    void breedOrganisms(); // Make every organism in the city breed.
};

#endif // WORLD_H
