#include <iostream>
#include "Organism.h"
#include "City.h"

// Create an organism at the given coordinates in the given world.
Organism::Organism(City* aWorld, int xcoord, int ycoord) {
    world = aWorld;
    x = xcoord;
    y = ycoord;
    breedTicks = 0;
    moved = false;
    world->setOrganism(x, y, this);
}

// flags the organism as moved or not
void Organism::setMoved(bool hasMoved) {
    moved = hasMoved;
}

// Check if organism has moved
bool Organism::hasMoved() const {
    return moved;
}

// Move the organism to its new position and null the old one
void Organism::movesTo(int xNew, int yNew) {
    world->setOrganism(xNew, yNew, world->getOrganism(x, y));
    world->setOrganism(x, y, NULL);
    x = xNew;
    y = yNew;
    world->getOrganism(x, y)->setMoved(true);
}

// Checks if organism is within the grid
bool Organism::inGrid(int x, int y)
{
    return (x >= 0) && (x < CITYSIZE) && (y >= 0) && (y < CITYSIZE);
}

// Check if organism is dead
bool Organism::isDead() const {
    return false;
}
