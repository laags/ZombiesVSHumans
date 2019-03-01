#include <cstdlib>
#include <iostream>
#include "Human.h"
#include "Organism.h"
#include "City.h"
using namespace std;

Human::Human(City* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord) {}

// Make a random move within the grid
void Human::move()
{
    breedTicks++;
    Move currentMove = world->randomMove();
    switch (currentMove){
        case UP:
            if(world->getOrganism(x, y + 1) == NULL && inGrid(x, y + 1))
            {
                movesTo(x, y + 1);
            }
            break;
        case DOWN:
            if(world->getOrganism(x, y - 1) == NULL && inGrid(x, y - 1))
            {
                movesTo(x, y - 1);
            }
            break;
        case LEFT:
            if(world->getOrganism(x - 1, y) == NULL && inGrid(x - 1, y))
            {
                movesTo(x - 1, y);
            }
            break;
        case RIGHT:
            if(world->getOrganism(x + 1, y) == NULL && inGrid(x + 1, y))
            {
                movesTo(x + 1, y);
            }
            break;
        default:
            break;
    }
}

// Polymorphic breed (recruit)
void Human::breed()
{
    if(breedTicks >= HUMAN_BREEDCOUNT)
    {
        recruitAdjacent();
    }
}

// Search for valid grid position to recruit
void Human::recruitAdjacent()  {
    if((world->getOrganism(x, y + 1) == NULL) && inGrid(x, y + 1))
    {
        generateRecruit(x, y + 1);
    }
    else if((world->getOrganism(x, y - 1) == NULL) && inGrid(x, y - 1))
    {
        generateRecruit(x, y - 1);
    }
    else if((world->getOrganism(x - 1, y) == NULL)  && inGrid(x - 1, y))
    {
        generateRecruit(x - 1, y);
    }
    else if((world->getOrganism(x + 1, y) == NULL)  && inGrid(x + 1, y))
    {
        generateRecruit(x + 1, y);
    }
    breedTicks = 0;
}

// Generate the new recruit
void Human::generateRecruit(int whereX, int whereY)
{
    new Human(this->world, whereX, whereY);
    breedTicks = 0;
}

OrganismType Human::getType() const
{
    return HUMAN;
}

// The letter that represents the human on the grid
char Human::representation() const
{
    return 'H';
}

// Check if a position is in the grid
bool Human::inGrid(int x, int y)
{
    return (x >= 0) && (x < CITYSIZE) && (y >= 0) && (y < CITYSIZE);
}