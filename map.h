#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.h"
#include <tuple>
#include "qdebug.h"
#include "qlogging.h"
#include <fstream>


class Map
{
public:
    Map();
    Map(int x, int y, int initial_food, int initial_population, int max_speed);
    void populateMap();
    void placeNewFood();
    void placeNewAnimals();
    void searchMap(int direction, int type);

    bool isInitialized();

    std::vector<std::vector<int>>& getMapGrid();

    bool isValidCell(int ROW, int COL);

    void setGridCell(int ROW, int COL, int VALUE);
    int getGridCellValue(int ROW, int COL);

    void animalMouvement();

    std::tuple<int, int> radialFoodSearch(int ROW, int COL, int RADIUS); // food search from animal cell in radius


private:
    int ROW_SIZE;
    int COL_SIZE;
    int INITIAL_POP;
    int INITIAL_FOOD;
    int MAX_SPEED;
    bool initialized = false;
    // int FRAME_UPDATE_MS = 500; // 1000ms = 1s

    int turns_count = 0;

    std::vector<std::vector<int>> matrix;
    std::vector<Animal> animals;
};

#endif // MAP_H
