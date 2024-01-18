#include <iostream>
#include <cstdlib>
#include <vector>

struct Game {
private:
    int gridSize;
    int hasWon = 0;
    std::vector<std::vector<int>> grid; // the actual grid of the tic tac toe game
    // 0 indicates not filled
    // 1 indicates player 1 (X)
    // 2 indicates plyaer 2 (O)
    std::vector<std::vector<char>> displayedGrid; // matrix representation of the grid players see

    /**
     * @brief fills/updates the displayed grid according to the game progress.
     * 
     */
    void updateDisplayedGrid() {
        int row, col;
        row = col = 0;
        for (int i = 0; i < (int) displayedGrid.size(); i++) {
            if (!(i%2)) { // if row is not a grid row
                for (int j = 0; j < (int) displayedGrid[0].size(); j++) {
                    if (j%2) { // if odd/grid line
                        displayedGrid[i][j] = '|';

                    } else if (grid[row][col] == 1) { // player 1
                        displayedGrid[i][j] = 'X';
                        col++;

                    } else if (grid[row][col] == 2){ // player 2
                        displayedGrid[i][j] = 'O';
                        col++;

                    } else { // empty box
                        displayedGrid[i][j] = ' ';
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

    /**
     * @brief displays grid.
     * 
     */
    void displayGrid() {
        updateDisplayedGrid();
        for (int i = 0; i < (int) displayedGrid.size(); i++) {
            for (int j = 0; j < (int) displayedGrid[0].size(); j++) {
                std::cout << displayedGrid[i][j];
            }
            std::cout << std::endl;
        }
    }

    void updateGame(int row, int col, int player) {
        grid[row-1][col-1] = player; // -1 to accommodate grid starting at pos 0
        bool horizontalWin, verticalWin;    // flags to indicate if horizontal/vertical wins are possible

        // check horizontal and vertical win
        for (int i = 0; i < gridSize; i++) {
            horizontalWin = verticalWin = true;

            for (int j = 0; j < gridSize; j++) {
                if (horizontalWin && grid[i][j] != player) 
                    horizontalWin = false;

                if (verticalWin && grid[j][i] != player)
                    verticalWin = false;
                
                // if both wins are no longer possible, break
                if (!verticalWin && !horizontalWin)
                    break;
                
                if (j == gridSize-1) {
                    hasWon = player;
                    return;
                }
            }
        }

        // check diagonal win
        bool leftRight, rightLeft; // flags to indicate if the two diagonals possibility are possible
        leftRight = rightLeft = true;
        int j = gridSize-1; // to iterate through top right to bot left diagonal

        for (int i = 0; i < gridSize; i++) {
            if (leftRight && grid[i][i] != player)
                leftRight = false;
            
            if (rightLeft && grid[i][j] != player)
                rightLeft = false;
            
            if (!rightLeft && !leftRight)
                break;

            else if (i == gridSize-1) {
                hasWon = player;
                return;
            }
            j--;
        }
    }

public:
    Game() {
        this->gridSize = 3;
        this->grid = std::vector<std::vector<int>>(3, std::vector<int>(3));
        this->displayedGrid = std::vector<std::vector<char>>(5, std::vector<char>(5));
        updateDisplayedGrid();
    }

    Game(int n) {
        this->gridSize = n;
        this->grid = std::vector<std::vector<int>>(n, std::vector<int>(n));
        this->displayedGrid = std::vector<std::vector<char>>(n*2-1, std::vector<char>(n*2-1));
        updateDisplayedGrid();
    } 

    void start() {
        std::cout << "Game start!\n";
        displayGrid();
        int filled = 0; // boxes filled

        while (!hasWon && filled < gridSize*gridSize) {
            int delimiterPos;

            std::cout << "Player 1, enter your box (row,column): ";
            std::string coords;
            std::cin >> coords;
            delimiterPos = coords.find(',');
            updateGame(stoi(coords.substr(0, delimiterPos)), stoi(coords.substr(delimiterPos+1)), 1);
            displayGrid();
            filled++;
            if (hasWon || filled >= gridSize*gridSize) break;
            

            std::cout << "Player 2, enter your box (row,column): ";
            std::cin >> coords;
            delimiterPos = coords.find(',');
            updateGame(stoi(coords.substr(0, delimiterPos)), stoi(coords.substr(delimiterPos+1)), 2);
            displayGrid();
            filled++;
        } 

        if (hasWon)
            std::cout << "Player " << hasWon << " won!\n";
        else
            std::cout << "Tied!\n";
    }
};

int main() {
    Game g;
    g.start();

    return 0;
}