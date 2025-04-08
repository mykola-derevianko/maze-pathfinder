#include <queue>
#include <stack>
#include <utility>
#include <vector>
#include <memory>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Cell.hpp"

const int CELL_SIZE = 40;
const int DELAY_IN_MS = 50;

int main() {
    const int rows = 15;
    const int cols = 15;
    std::vector<std::vector<int>> maze(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {rows - 1, cols - 1};

    std::vector<std::vector<int>> possibleMoves = {
            {-1, 0}, {1,  0}, {0, -1}, {0, 1}
    };

    std::queue<std::shared_ptr<Cell>> queue;
    std::shared_ptr<Cell> endCell = nullptr;
    bool solving = false;
    bool bfsStarted = false;
    bool settingStart = true;

    sf::RenderWindow window(sf::VideoMode(cols * CELL_SIZE, rows * CELL_SIZE), "MazePathfinder by Mykola Derevianko");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!solving && event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.y / CELL_SIZE;
                int y = event.mouseButton.x / CELL_SIZE;

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (std::make_pair(x, y) != start && std::make_pair(x, y) != end)
                            maze[x][y] = 1 - maze[x][y];
                    }
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        if (settingStart) {
                            if (std::make_pair(x, y) != end) start = {x, y};
                            settingStart = false;
                        } else {
                            if (std::make_pair(x, y) != start) end = {x, y};
                            settingStart = true;
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !solving) {
                solving = true;
                bfsStarted = true;
                visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
                queue = std::queue<std::shared_ptr<Cell>>();
                endCell = nullptr;
                auto startCell = std::make_shared<Cell>(start.first, start.second);
                visited[start.first][start.second] = true;
                queue.push(startCell);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                maze = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
                visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
                queue = std::queue<std::shared_ptr<Cell>>();
                endCell = nullptr;
                solving = false;
                bfsStarted = false;
            }
        }

        if (solving && bfsStarted && !queue.empty() && !endCell) {
            auto current = queue.front();
            queue.pop();

            if (current->x == end.first && current->y == end.second) {
                endCell = current;
            } else {
                for (const auto &move: possibleMoves) {
                    int newX = current->x + move[0];
                    int newY = current->y + move[1];

                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                        maze[newX][newY] == 0 && !visited[newX][newY]) {
                        visited[newX][newY] = true;
                        auto nextCell = std::make_shared<Cell>(newX, newY, current);
                        queue.push(nextCell);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_IN_MS));
        }

        window.clear();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);

                if (maze[i][j] == 1) {
                    cell.setFillColor(sf::Color::Black);
                } else if (std::make_pair(i, j) == start) {
                    cell.setFillColor(sf::Color::Blue);
                } else if (std::make_pair(i, j) == end) {
                    cell.setFillColor(sf::Color::Red);
                } else if (visited[i][j]) {
                    cell.setFillColor(sf::Color{105, 115, 255});
                } else {
                    cell.setFillColor(sf::Color::White);
                }

                window.draw(cell);
            }
        }

        if (endCell) {
            for (auto cur = endCell; cur != nullptr; cur = cur->parent) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                cell.setPosition(cur->y * CELL_SIZE, cur->x * CELL_SIZE);
                cell.setFillColor(sf::Color::Green);
                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}
