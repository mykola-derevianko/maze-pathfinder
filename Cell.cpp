#include "Cell.hpp"

Cell::Cell(int x, int y, std::shared_ptr<Cell> parent)
    : x(x), y(y), parent(std::move(parent)) {}
