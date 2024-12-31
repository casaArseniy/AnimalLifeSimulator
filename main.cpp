#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

// // Function to perform a triangular scan
// Point triangularScan(const Grid& grid, Point animalCell, int height) {
//     int x = animalCell.first;
//     int y = animalCell.second;

//     for (int h = 1; h <= height; ++h) {
//         for (int dx = -h; dx <= h; ++dx) {
//             int nx = x + h;
//             int ny = y + dx;

//             if (isValidPoint(grid, nx, ny) && grid[nx][ny] == 1) {
//                 return {nx, ny};
//             }
//         }
//     }

//     return {-1, -1}; // Return invalid point if not found
// }

// // Function to perform a rectangular scan
// Point rectangularScan(const Grid& grid, Point animalCell, int width, int length) {
//     int x = animalCell.first;
//     int y = animalCell.second;

//     for (int l = 1; l <= length; ++l) {
//         for (int w = -width / 2; w <= width / 2; ++w) {
//             int nx = x + l;
//             int ny = y + w;

//             if (isValidPoint(grid, nx, ny) && grid[nx][ny] == 1) {
//                 return {nx, ny};
//             }
//         }
//     }

//     return {-1, -1}; // Return invalid point if not found
// }

// // Example usage
// int main() {
//     Grid grid = {
//         {0, 0, 0, 0, 0},
//         {0, 1, 0, 1, 0},
//         {0, 0, 0, 0, 0},
//         {0, 1, 0, 1, 0},
//         {0, 0, 0, 0, 0}
//     };

//     Point animalCell = {2, 2};

//     // Radial scan
//     Point result1 = radialScan(grid, animalCell, 2);
//     std::cout << "Radial Scan Result: (" << result1.first << ", " << result1.second << ")\n";

//     // Triangular scan
//     Point result2 = triangularScan(grid, animalCell, 2);
//     std::cout << "Triangular Scan Result: (" << result2.first << ", " << result2.second << ")\n";

//     // Rectangular scan
//     Point result3 = rectangularScan(grid, animalCell, 2, 3);
//     std::cout << "Rectangular Scan Result: (" << result3.first << ", " << result3.second << ")\n";

//     return 0;
// }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
