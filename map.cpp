#include "map.h"

Map::Map() {
    this->COL_SIZE = 0;
    this->ROW_SIZE = 0;
    this->INITIAL_FOOD = 0;
    this->INITIAL_POP = 0;
    this->MAX_SPEED = 0;
    this->initialized = false;
    this->matrix = std::vector<std::vector<int>>(this->ROW_SIZE, std::vector<int>(this->COL_SIZE, 0)); //create a tilemap for window
}

Map::Map(int x, int y, int initial_food, int initial_population, int max_speed) {
    this->COL_SIZE = x;
    this->ROW_SIZE = y;
    this->matrix = std::vector<std::vector<int>>(this->ROW_SIZE, std::vector<int>(this->COL_SIZE, 0)); //create a tilemap for window

    this->INITIAL_FOOD = initial_food;
    this->INITIAL_POP = initial_population;
    this->MAX_SPEED = max_speed;
    this->initialized = true;
}

bool Map::isInitialized(){
    return this->initialized;
}

void Map::populateMap() {

    std::srand(std::time(nullptr));
    int randomRow, randomCol, randomSpeed;

    //initial animal population
    for (int i = 0; i < this->INITIAL_POP; i++) {
        randomRow = std::rand() % ROW_SIZE;
        randomCol = std::rand() % COL_SIZE;
        randomSpeed = std::rand() % this->MAX_SPEED + 5; // max_speed = 20
        Animal randomAnimal;
        randomAnimal.setCOL(randomCol);
        randomAnimal.setROW(randomRow);
        randomAnimal.setSpeed(randomSpeed);
        randomAnimal.setLimit(randomAnimal.getSpeed()*3);
        this->animals.push_back(randomAnimal);

        matrix[randomRow][randomCol] = 2;
    }

    //initial food
    for (int i = 0; i < INITIAL_FOOD; i++) {
        randomRow = std::rand() % ROW_SIZE;
        randomCol = std::rand() % COL_SIZE;
        matrix[randomRow][randomCol] = 1;
    }
}

void Map::setGridCell(int ROW, int COL, int VALUE) {
    this->matrix[ROW][COL] = VALUE;
}

int Map::getGridCellValue(int ROW, int COL) {
    return this->matrix[ROW][COL];
}

std::vector<std::vector<int>>& Map::getMapGrid() {
    return this->matrix;
}

bool Map::isValidCell(int ROW, int COL) {
    return ROW >= 0 && COL >= 0 && ROW < this->ROW_SIZE && COL < this->COL_SIZE;
}

void Map::animalMouvement() {
    std::srand(std::time(nullptr));

    std::ofstream outFile("log.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        exit(1);
    }

    outFile<< "TURN COUNT: " << this->turns_count << "\n";

    for (auto it = this->animals.begin(); it != this->animals.end(); ) {

        int oldRow = it->getROW();
        int oldCol = it->getCOL();
        this->matrix[oldRow][oldCol] = 0;

        outFile << "Animal with speed "<< it->getSpeed()<< " is at position x:"<< oldRow << " y:" << oldCol <<"\n";
        outFile << "Movement Count: " << it->getMovementCount() << "\n" ;

        // If the animal is dead, erase it and continue
        if (it->isDead()) {
            it = this->animals.erase(it);
            outFile << "Has died at turn " <<this->turns_count << "\n";
            //std::cout<<"Animal with speed "<< it->getSpeed() <<" died at turn "<<this->turns_count<<std::endl;
            continue;
        }

        // Calculate movement of the animal
        int x, y;
        std::tie(x, y) = radialFoodSearch(oldRow, oldCol, it->getSpeed());

        if (x != -1 && y != -1) {
            it->setCOL(y);
            it->setROW(x);
            this->matrix[x][y] = 2;
            it->incrementResultingMovement(oldCol, oldRow, x, y);
            it->reduceEnergy();

            it->incrementEnergy();
            ++it;
            continue;
        }

        // Generates -1, 0, or 1
        int newROW = (std::rand() % 3 - 1) * it->getSpeed();
        int newCOL = (std::rand() % 3 - 1) * it->getSpeed();

        while (!isValidCell(oldRow + newROW, oldCol + newCOL)) {
            newROW = (std::rand() % 3 - 1) * it->getSpeed();
            newCOL = (std::rand() % 3 - 1) * it->getSpeed();
        }

        // Increment movement
        it->incrementResultingMovement(oldCol, oldRow, oldCol + newCOL, oldRow + newROW);

        outFile << "Has moved to position x: " << oldCol + newCOL << " y: " << oldRow + newROW << "\n";

        // Reduce energy
        it->reduceEnergy();

        // Move animal
        it->setCOL(oldCol + newCOL);
        it->setROW(oldRow + newROW);
        this->matrix[oldRow + newROW][oldCol + newCOL] = 2;

        ++it;
    }

    this->turns_count += 1;
    outFile.close(); // Close the file

}

std::tuple<int, int> Map::radialFoodSearch(int ROW, int COL, int RADIUS) {

    for (int r = 1; r <= RADIUS; ++r) {
        for (int dx = -r; dx <= r; ++dx) {
            int dy = r - abs(dx);
            int x1 = COL + dx, y1 = ROW + dy;
            int x2 = COL + dx, y2 = ROW - dy;

            if (this->isValidCell(x1, y1) && this->matrix[x1][y1] == 1) {
                return std::make_tuple(x1, y1);
            }
            if (dy != 0 && this->isValidCell(x2, y2) && this->matrix[x2][y2] == 1) {
                return std::make_tuple(x2, y2);
            }
        }
    }

    return std::make_tuple(-1, -1); // Return invalid point if not found
}

void Map::placeNewAnimals(){}
void Map::placeNewFood(){}
