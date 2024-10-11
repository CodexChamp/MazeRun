#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include "MazeAlgorithms.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void drawMaze(sf::RenderWindow& window, const std::vector<std::vector<Cell>>& maze) {
    const int cellSize = 20; // Size of each cell
    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
            cellShape.setPosition(x * cellSize, y * cellSize);
            if (maze[y][x] == Cell::WALL) {
                cellShape.setFillColor(sf::Color::Black); // Wall color
            }
            else {
                cellShape.setFillColor(sf::Color::White); // Path color
            }
            window.draw(cellShape);
        }
    }
}

void printMaze(const std::vector<std::vector<Cell>>& maze) {
    // Create a temporary image of the maze to print
    const int cellSize = 20;
    const int width = maze[0].size() * cellSize;
    const int height = maze.size() * cellSize;

    sf::RenderTexture renderTexture;
    renderTexture.create(width, height);

    // Draw the maze into the render texture
    for (size_t y = 0; y < maze.size(); ++y) {
        for (size_t x = 0; x < maze[y].size(); ++x) {
            sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
            cellShape.setPosition(x * cellSize, y * cellSize);
            if (maze[y][x] == Cell::WALL) {
                cellShape.setFillColor(sf::Color::Black);
            }
            else {
                cellShape.setFillColor(sf::Color::White);
            }
            renderTexture.draw(cellShape);
        }
    }
    renderTexture.display();
    std::cout << "Attempting to print the maze..." << std::endl;

    // Save the texture to a file
    const std::string filename = "maze.png";
    sf::Image mazeImage = renderTexture.getTexture().copyToImage();
    mazeImage.saveToFile(filename);

    // Print the image using system command
    std::string command = "print " + filename; // Change to the appropriate print command for your OS
    system(command.c_str());
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Maze Generator");
    window.setFramerateLimit(60);

    // Button creation for maze generation
    sf::RectangleShape generateButton(sf::Vector2f(150, 50));
    generateButton.setPosition(WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 - 25);
    generateButton.setFillColor(sf::Color::Green);

    // Button creation for printing the maze
    sf::RectangleShape printButton(sf::Vector2f(150, 50));
    printButton.setPosition(WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 + 50);
    printButton.setFillColor(sf::Color::Blue);

    sf::Font font;
    if (!font.loadFromFile("C:/Projects/mazeRun/mazeRun/sources/CamingoCode-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1; // Exit if font loading fails
    }

    sf::Text buttonText("Generate Maze", font, 20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 15);

    sf::Text printText("Print Maze", font, 20);
    printText.setFillColor(sf::Color::White);
    printText.setPosition(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2 + 65);

    std::vector<std::vector<Cell>> maze(21, std::vector<Cell>(21, Cell::WALL)); // Initialize maze with walls
    bool mazeGenerated = false; // Flag to check if maze has been generated

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (generateButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        recursiveBacktracking(maze); // Call the maze generation algorithm
                        mazeGenerated = true; // Set flag to true
                    }

                    if (printButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && mazeGenerated) {
                        printMaze(maze); // Call the print maze function
                    }
                }
            }
        }

        window.clear();
        window.draw(generateButton);
        window.draw(buttonText);
        window.draw(printButton);
        window.draw(printText);

        // If maze is generated, draw it
        if (mazeGenerated) {
            drawMaze(window, maze);
        }

        window.display();
    }

    return 0;
}
