#include <iostream>
#include <cstdlib>  // for rand
#include <windows.h>
#include <conio.h>
#include "City.h"
#include "Human.h"
#include "Zombie.h"
using namespace std;

void Col(int);

// Constructor, takes a seed for randoms
City::City(unsigned int seed) {
    srand(seed);
    // Create create the city
    for (int i = 0; i < CITYSIZE; i++) {
        for (int j = 0; j < CITYSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // Create the organisms
    createOrganisms(HUMAN, HUMAN_STARTCOUNT);
    createOrganisms(ZOMBIE, ZOMBIE_STARTCOUNT);
}

// Deconstructor
City::~City() {
    for (int i = 0; i < CITYSIZE; i++) {
        for (int j = 0; j < CITYSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the coordinates or NULL of nothing is there
Organism* City::getOrganism(int x, int y) const {
    if ((x >= 0) && (x < CITYSIZE) && (y >= 0) && (y < CITYSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the position in grid to the organism passed in
void City::setOrganism(int x, int y, Organism *org) {
    if ((x >= 0) && (x < CITYSIZE) && (y >= 0) && (y < CITYSIZE)) {
        grid[x][y] = org;
    }
}

// Checks if an extinction level event has occurred
bool City::isExtinct() {
    bool zombiesExtinct = true, humansExtinct = true;
    for (int j = 0; j < CITYSIZE; j++) {
        for (int i = 0; i < CITYSIZE; i++) {
            if (grid[i][j] != NULL) {
                if (grid[i][j]->getType() == HUMAN) {
                    humansExtinct = false;
                } else if (grid[i][j]->getType() == ZOMBIE) {
                    zombiesExtinct = false;
                }
            }
        }
    }
    if(zombiesExtinct || humansExtinct)
        return true;
    return false;
}

// Displays the current city and counts of organisms
void City::displayCity() const {
    int humanCount = 0;
    int zombieCount = 0;
    cout << endl << endl;
    for (int j = 0; j < CITYSIZE; j++) {
        for (int i = 0; i < CITYSIZE; i++) {
            if (grid[i][j] == NULL) {
                Col(7);
                cout << "#  ";
            } else {
                if (grid[i][j]->getType() == HUMAN) {
                    humanCount++;
                    Col(1);

                }
                else if (grid[i][j]->getType() == ZOMBIE) {
                    zombieCount++;
                    Col(12);
                }
                cout << grid[i][j]->representation() << "  ";
            }
        }
        cout << endl;
    }
    Col(7);
    cout << "Current Organism Count:" << endl;
    cout << "Humans: " << humanCount << " Zombies: " << zombieCount << endl;
}

// A step in the city
void City::step() {
    resetOrganisms(); // Reset organisms moved state
    moveOrganism(ZOMBIE);
    moveOrganism(HUMAN);
    cleanup(); // Check for starved zombies
    breedOrganisms();
}

// Returns a random position
Position City::randomPosition() const {
    Position pos;
    pos.x = rand() % CITYSIZE;
    pos.y = rand() % CITYSIZE;
    return pos;
}

// Returns a random move
Move City::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

// Populates the city putting in the humans and zombies into empty spots
void City::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == HUMAN) {
                new Human(this, p.x, p.y);
            }
            else if (orgType == ZOMBIE) {
                new Zombie(this, p.x, p.y);
            }
        }
    }
}

// Reset all organisms to not moved
void City::resetOrganisms() {
    for(int i = 0; i < CITYSIZE; i++)
    {
        for (int j = 0; j < CITYSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of the provided type
void City::moveOrganism(OrganismType aType) {
    for(int i = 0; i < CITYSIZE; i++)
    {
        for(int j = 0; j < CITYSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove dead zombies and replaces them with humans
void City::cleanup() {
    for (int i = 0; i < CITYSIZE; i++) {
        for (int j = 0; j < CITYSIZE; j++) {
            // Check for zombies that havent eaten
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = new Human(this, i, j);
            }
        }
    }
}

// Breed organisms
void City::breedOrganisms() {
    for(int i = 0; i < CITYSIZE; i++)
    {
        for(int j = 0; j < CITYSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}

//Change color
void Col(int c)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
    return;
}
