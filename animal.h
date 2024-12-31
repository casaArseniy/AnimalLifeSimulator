#ifndef ANIMAL_H
#define ANIMAL_H

#include <cmath>
#include "qdebug.h"
#include "qlogging.h"

class Animal
{
public:
    Animal();
    ~Animal();
    void setROW(int ROW);
    void setCOL(int COL);
    void setLifetime(int age);
    void setSpeed(int pxl);
    void setEnergy(int energy);
    void setLimit(int limit);

    int getROW();
    int getCOL();
    int getLifetime();
    int getAge();
    int getSpeed();
    int getEnergy();

    int getMovementCount();

    void incrementResultingMovement(int old_x, int old_y, int new_x, int new_y);
    void incrementEnergy();
    void reduceEnergy();
    void incrementAge();

    bool isDead();



private:
    int ROW = 0;
    int COL = 0;
    int lifetime = 0;
    int age = 0;
    int speed = 1;
    int energy = 1;

    int movement_until_hunger = 0;
    int limit = 1;

};

#endif // ANIMAL_H
