#include "MazeAlgorithms.h"
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>    
#include <stack>
#include <vector>

void recursiveBacktracking(std::vector<std::vector<Cell>>& maze) {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    int width = maze.size();
    int height = maze[0].size();

    // Start at a random cell
    int startX = 1 + 2 * (rand() % ((width - 1) / 2));
    int startY = 1 + 2 * (rand() % ((height - 1) / 2));
    maze[startY][startX] = Cell::PATH; // Mark the start cell as a path

    std::stack<std::pair<int, int>> stack; // Stack to hold the cells to visit
    stack.push({ startX, startY });

    // Define possible directions for movement
    std::vector<std::pair<int, int>> directions = {
        {2, 0}, {-2, 0}, {0, 2}, {0, -2}
    };

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        std::vector<std::pair<int, int>> neighbors;

        // Check for neighboring cells that can be visited
        for (const auto& direction : directions) {
            int nx = x + direction.first;
            int ny = y + direction.second;

            // Ensure the neighbor is within bounds and is a wall
            if (nx > 0 && ny > 0 && nx < width && ny < height && maze[ny][nx] == Cell::WALL) {
                neighbors.push_back({ nx, ny });
            }
        }

        // If there are unvisited neighbors, choose one and carve a path
        if (!neighbors.empty()) {
            stack.push({ x, y }); // Push current cell back to stack

            // Randomly select one of the unvisited neighbors
            auto [nx, ny] = neighbors[rand() % neighbors.size()];
            maze[ny][nx] = Cell::PATH; // Mark as path

            // Carve a path between the current cell and the chosen neighbor
            maze[(y + ny) / 2][(x + nx) / 2] = Cell::PATH; // This carves the wall between the cells

            stack.push({ nx, ny }); // Push neighbor to stack
        }
    }
}




// You can implement Prim's and Kruskal's algorithms in a similar manner
