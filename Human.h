#ifndef INHERITANCE_AND_POLYMORPHISM_Human
#define INHERITANCE_AND_POLYMORPHISM_Human

#include <iostream>
#include "Organism.h"
#include "City.h"

class Human : public Organism
{
public:

    Human(City* aWorld, int xcoord, int ycoord);
    void move(); // Move the human
    void breed(); // Breed the human (recruit).
    OrganismType getType() const; // Get the organisms type
    char representation() const; // Character that represents the human
    bool inGrid(int x, int y); // Check if position is in grid

private:
    void generateRecruit(int whereX, int whereY); // Recruit a Human at provided position
    void recruitAdjacent(); // Checks if recruiting is possible
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Ant__) */
