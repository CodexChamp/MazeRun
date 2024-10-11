#ifndef MAZEALGORITHMS_H
#define MAZEALGORITHMS_H

#include <vector>

// Enum for cell state
enum Cell { WALL, PATH };

// Function declarations for maze algorithms
void recursiveBacktracking(std::vector<std::vector<Cell>>& maze);
void primAlgorithm(std::vector<std::vector<Cell>>& maze);
void kruskalAlgorithm(std::vector<std::vector<Cell>>& maze);

#endif // MAZEALGORITHMS_H
