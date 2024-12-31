#include "animal.h"

Animal::Animal() {}
Animal::~Animal() {}


void Animal::incrementResultingMovement(int old_x, int old_y, int new_x, int new_y) {
    this->movement_until_hunger += sqrt(pow(new_x - old_x, 2) + pow(new_y - old_y, 2));
    //qDebug() << movement_until_hunger;
}

int Animal::getMovementCount() {
    return this->movement_until_hunger;
}

bool Animal::isDead() {
    if (this->energy <= 0) {
        return true;
    }
    return false;
}

void Animal::setCOL(int COL){
    this->COL = COL;
}
void Animal::setROW(int ROW){
    this->ROW = ROW;
}
void Animal::setLifetime(int age){
    this->lifetime = age;
}
void Animal::setSpeed(int pxl) {
    this->speed = pxl;
}
void Animal::setEnergy(int energy) {
    this->energy = energy;
}

void Animal::setLimit(int limit) {
    this->limit = limit;
}

void Animal::incrementAge() {
    this->age += 1;
}
void Animal::incrementEnergy() {
    this->energy += 1;
}

void Animal::reduceEnergy() {
    if (this->movement_until_hunger >= this->limit) {
        this->energy -= 1;
        this->movement_until_hunger = 0;
    }
}

int Animal::getCOL() {
    return this->COL;
}
int Animal::getROW() {
    return this->ROW;
}
int Animal::getLifetime() {
    return this->lifetime;
}
int Animal::getAge() {
    return this->age;
}
int Animal::getSpeed() {
    return this->speed;
}
int Animal::getEnergy() {
    return this->energy;
}
