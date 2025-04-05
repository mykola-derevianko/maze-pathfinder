#include <iostream>
#include <queue>
#include <stack>

struct Cell{
    int x;
    int y;
    Cell* parent;
    Cell(int x, int y, Cell* parent = nullptr) : x(x), y(y), parent(parent) {};
};

int main() {
    std::vector<std::vector<int>> maze = {
            {0, 1, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 0, 1, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 0, 0, 0}
    };
    int rows = maze.size();
    int cols = maze[0].size();

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {4, 4};
    std::vector<std::vector<int>> possibleMoves = {{-1,0},{1,0},{0,-1},{0,1}};

    std::queue<Cell*> queue;
    Cell* startCell = new Cell(start.first, start.second);
    Cell* endCell = nullptr;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    queue.push(startCell);
    visited[start.first][start.second] = true;
    while(!queue.empty()){
        Cell* current = queue.front();
        queue.pop();

        if(current->x == end.first && current->y == end.second){
            endCell = current;
            break;
        }
        for(auto move : possibleMoves){
            int newX = current->x + move[0];
            int newY = current->y + move[1];

            if(newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
               maze[newX][newY] == 0 && !visited[newX][newY]){
                visited[newX][newY] = true;
                Cell* nextCell = new Cell(newX, newY, current);
                queue.push(nextCell);
            }
        }
    }
    if (endCell != nullptr) {
        std::stack<std::pair<int, int>> path;
        for (Cell* cur = endCell; cur != nullptr; cur = cur->parent) {
            path.push({cur->x, cur->y});
        }

        std::vector<std::vector<char>> visualizedMaze;
        for(auto row : maze){
            std::vector<char> temp;
            std::transform(row.begin(), row.end(), std::back_inserter(temp), [](const int &i){ return '0'+i; });
            visualizedMaze.push_back(std::move(temp));
        }

        while(!path.empty()){
            visualizedMaze[path.top().first][path.top().second] = '#';
            path.pop();
        }

        //Print maze with path
        for(auto row : visualizedMaze){
            for(auto c : row){
                std::cout<<c << " ";
            }
            std::cout<<std::endl;
        }
    } else {
        std::cout << "No path found.\n";
    }


}
