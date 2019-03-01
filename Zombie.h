#ifndef INHERITANCE_AND_POLYMORPHISM_Zombie
#define INHERITANCE_AND_POLYMORPHISM_Zombie

#include <iostream>
#include "City.h"
#include "Organism.h"

class Zombie : public Organism
{
public:

    Zombie(City* aWorld, int xcoord, int ycoord);
    void move(); // Move the zombie
    void breed(); // Breed the zombie (Convert)
    OrganismType getType() const; // Get the zombies type
    char representation() const; // Character that represents the zombie
    bool isDead() const; // Check if zombie starved
    bool inGrid(int x, int y); // Check if position in grid

private:
    void generateConvert(int whereX, int whereY); // Convert to a Zombie at provided position
    void convertNearby(); // Try to convert nearby human
    int death_tik; // counter for starvation
};

#endif /* defined(__INHERITANCE_AND_POLYMORPHISM__Bug__) */
