#include <iostream>
#include <cstdlib>
#include <vector>

struct Game {
private:
    int gridSize;
    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<char>> displayedGrid;

    void fillDisplayedGrid() {
        int row, col;
        row = col = 0;
        for (int i = 0; i < (int) displayedGrid.size(); i++) {
            if (!(i%2)) { // if row is not a grid row
                for (int j = 0; j < (int) displayedGrid[0].size(); j++) {
                    if (j%2) { // if odd/grid line
                        displayedGrid[i][j] = '|';
                    } else if (grid[row][col]) {
                        displayedGrid[i][j] = 'X';
                        col++;
                    } else {
                        displayedGrid[i][j] = 'O';
                        col++;
                    }
                }
                row++;
            } else {
                for (int j = 0; j < (int) displayedGrid[0].size(); j++) {
                    j%2? displayedGrid[i][j] = '+' : displayedGrid[i][j] = '-';
                }
            }  
            col = 0;
        }   
    }

public:
    Game() {
        this->gridSize = 3;
        this->grid = std::vector<std::vector<bool>>(3, std::vector<bool>(3));
        this->displayedGrid = std::vector<std::vector<char>>(5, std::vector<char>(5));
        fillDisplayedGrid();
    }

    Game(int n) {
        this->gridSize = n;
        this->grid = std::vector<std::vector<bool>>(n, std::vector<bool>(n));
        this->displayedGrid = std::vector<std::vector<char>>(n*2-1, std::vector<char>(n*2-1));
        fillDisplayedGrid();
    }

    void displayGrid() {
        for (int i = 0; i < (int) displayedGrid.size(); i++) {
            for (int j = 0; j < (int) displayedGrid[0].size(); j++) {
                std::cout << displayedGrid[i][j];
            }
            std::cout << std::endl;
        }
    }
};

void displayGrid() {

}

int main() {
    Game g;
    g.displayGrid();

    return 0;
}