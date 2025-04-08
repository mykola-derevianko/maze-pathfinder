#ifndef SFML_GAME_CELL_HPP
#define SFML_GAME_CELL_HPP


#include <memory>

class Cell {
public:
    int x;
    int y;
    std::shared_ptr<Cell> parent;
    Cell(int x, int y, std::shared_ptr<Cell> parent = nullptr);
};


#endif //SFML_GAME_CELL_HPP
