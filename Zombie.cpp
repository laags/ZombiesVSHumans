#include <chrono>
#include <vector>
#include <random>
#include <algorithm>
#include "Zombie.h"
#include "Organism.h"
using namespace std;

Zombie::Zombie(City* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    death_tik = 0;
}

// Move the zombie by first trying to eat valid targets, then moving normally otherwise
void Zombie::move()
{
    breedTicks++;
    death_tik++;

    // Check for human to eat
    // Down
    if(world->getOrganism(x, y + 1) != NULL)
    {
        if(world->getOrganism(x, y + 1)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x, y + 1);
            movesTo(x, y + 1);
            return;
        }
    }

    // Up
    if(world->getOrganism(x, y - 1) != NULL)
    {
        if(world->getOrganism(x, y - 1)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x, y - 1);
            movesTo(x, y - 1);
            return;
        }
    }

    // Left
    if(world->getOrganism(x - 1, y) != NULL)
    {
        if(world->getOrganism(x - 1, y)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x - 1, y);
            movesTo(x - 1, y);
            return;
        }
    }

    // Right
    if(world->getOrganism(x + 1, y) != NULL)
    {
        if(world->getOrganism(x + 1, y)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x + 1, y);
            movesTo(x + 1, y);
            return;
        }
    }

    // Down/Left
    if(world->getOrganism(x - 1, y - 1) != NULL)
    {
        if(world->getOrganism(x - 1, y - 1)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x - 1, y - 1);
            movesTo(x - 1, y - 1);
            return;
        }
    }

    // Down/Right
    if(world->getOrganism(x + 1, y - 1) != NULL)
    {
        if(world->getOrganism(x + 1, y - 1)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x + 1, y - 1);
            movesTo(x + 1, y - 1);
            return;
        }
    }

    // Up/Left
    if(world->getOrganism(x - 1, y + 1) != NULL)
    {
        if(world->getOrganism(x - 1, y + 1)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x - 1, y + 1);
            movesTo(x - 1, y + 1);
            return;
        }
    }

    // Up/Right
    if(world->getOrganism(x + 1, y + 1) != NULL)
    {
        if(world->getOrganism(x + 1, y + 1)->getType() == HUMAN)
        {
            death_tik = 0;
            delete world->getOrganism(x + 1, y + 1);
            movesTo(x + 1, y + 1);
            return;
        }
    }

    // Otherwise randomly move
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

// Generate the new zombie in humans old position
void Zombie::generateConvert(int whereX, int whereY)
{
    new Zombie(this->world, whereX, whereY);
    breedTicks = 0;
}

// Attempt to breed (Convert)
void Zombie::breed()
{
    if(breedTicks >= ZOMBIE_BREEDCOUNT)
    {
        convertNearby();
    }

}

// Look for nearby human, delete it then spawn zombie in its place
void Zombie::convertNearby()  {
    vector<int> v = {};//populate vector
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock


    // Down
    if(world->getOrganism(x, y + 1) != NULL)
    {
        if(world->getOrganism(x, y + 1)->getType() == HUMAN)
        {
            v.push_back(1);
        }
    }

    // Up
    if(world->getOrganism(x, y - 1) != NULL)
    {
        if(world->getOrganism(x, y - 1)->getType() == HUMAN)
        {
            v.push_back(2);
        }
    }

    // Left
    if(world->getOrganism(x - 1, y) != NULL)
    {
        if(world->getOrganism(x - 1, y)->getType() == HUMAN)
        {
            v.push_back(3);
        }
    }

    // Right
    if(world->getOrganism(x + 1, y) != NULL)
    {
        if(world->getOrganism(x + 1, y)->getType() == HUMAN)
        {
            v.push_back(4);
        }
    }

    // Down/Left
    if(world->getOrganism(x - 1, y - 1) != NULL)
    {
        if(world->getOrganism(x - 1, y - 1)->getType() == HUMAN)
        {
            v.push_back(5);
        }
    }

    // Down/Right
    if(world->getOrganism(x + 1, y - 1) != NULL)
    {
        if(world->getOrganism(x + 1, y - 1)->getType() == HUMAN)
        {
            v.push_back(6);
        }
    }

    // Up/Left
    if(world->getOrganism(x - 1, y + 1) != NULL)
    {
        if(world->getOrganism(x - 1, y + 1)->getType() == HUMAN)
        {
            v.push_back(7);
        }
    }

    // Up/Right
    if(world->getOrganism(x + 1, y + 1) != NULL)
    {
        if(world->getOrganism(x + 1, y + 1)->getType() == HUMAN)
        {
            v.push_back(8);
        }
    }

    shuffle(v.begin(),v.end(),default_random_engine(seed));
    if(!v.empty()){
        if(v[0]==1){
            delete world->getOrganism(x, y + 1);
            generateConvert(x, y + 1);
        }
        else if(v[0]==2){
            delete world->getOrganism(x, y - 1);
            generateConvert(x, y - 1);
        }
        else if(v[0]==3){
            delete world->getOrganism(x - 1, y);
            generateConvert(x - 1, y);
        }
        else if(v[0]==4){
            delete world->getOrganism(x + 1, y);
            generateConvert(x + 1, y);
        }
        else if(v[0]==5){
            delete world->getOrganism(x - 1, y - 1);
            generateConvert(x - 1, y - 1);
        }
        else if(v[0]==6){
            delete world->getOrganism(x + 1, y - 1);
            generateConvert(x + 1, y - 1);
        }
        else if(v[0]==7){
            delete world->getOrganism(x - 1, y + 1);
            generateConvert(x - 1, y + 1);
        }
        else if(v[0]==8){
            delete world->getOrganism(x + 1, y + 1);
            generateConvert(x + 1, y + 1);
        }
    }
}

// Check if zombie starved
bool Zombie::isDead() const
{
    if(death_tik >= ZOMBIE_STARVECOUNT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Get the zombies type
OrganismType Zombie::getType() const
{
    return ZOMBIE;
}

// Character that represents the zombie
char Zombie::representation()const
{
    return 'Z';
}

// Check if pos in grid
bool Zombie::inGrid(int x, int y)
{
    return (x >= 0) && (x < CITYSIZE) && (y >= 0) && (y < CITYSIZE);
}
