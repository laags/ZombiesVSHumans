#ifndef ORGANISM_H
#define ORGANISM_H

// Enum for types of organisms
enum OrganismType {HUMAN, ZOMBIE};
class City;

class Organism {
public:
    Organism(City* aWorld, int xcoord, int ycoord); // Create organism at the provided coordinates.
    virtual ~Organism() { }
    virtual void move() = 0;
    virtual void breed() = 0;
    virtual OrganismType getType() const = 0; // Returns the type of organism.
    void setMoved(bool hasMoved); // Flag organism as having moved
    virtual char representation() const = 0;
//    virtual int size() const = 0;
    bool hasMoved() const; // Check if organism has moved this step
    virtual bool isDead() const; // Check if organism is dead
    bool inGrid(int x, int y); // Check if within the city grid

protected:
    void movesTo(int xNew, int yNew); // Move to provided position
    int x; // X position
    int y; // Y position
    bool moved; // Moved flag
    int breedTicks; // Ticks for breeding
    City* world; // Pointer to city organism belongs to
private:
};

#endif // ORGANISM_H
