#include <bits/stdc++.h>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char PLAYER_1_SYMBOL = 'X';
const char PLAYER_2_SYMBOL = 'O';

vector<vector<char> > board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY_CELL));

void printBoard() {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; i++) cout << setw(2) << i << "|";
    cout << "\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << setw(2) << i << "|";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << setw(2) << board[i][j];
            cout << '|';
        }
        cout << endl;
    }
}

bool checkWin(char playerSymbol) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        int count = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == playerSymbol) {
                count++;
                if (count == 5) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        int count = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j] == playerSymbol) {
                count++;
                if (count == 5) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }

    // Check diagonals
    for (int i = 0; i < BOARD_SIZE - 4; i++) {
        for (int j = 0; j < BOARD_SIZE - 4; j++) {
            if (board[i][j] == playerSymbol &&
                board[i + 1][j + 1] == playerSymbol &&
                board[i + 2][j + 2] == playerSymbol &&
                board[i + 3][j + 3] == playerSymbol &&
                board[i + 4][j + 4] == playerSymbol) {
                return true;
            }
            if (board[i][j + 4] == playerSymbol &&
                board[i + 1][j + 3] == playerSymbol &&
                board[i + 2][j + 2] == playerSymbol &&
                board[i + 3][j + 1] == playerSymbol &&
                board[i + 4][j] == playerSymbol) {
                return true;
            }
        }
    }

    return false;
}

bool checkTie() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL) {
                return false;
            }
        }
    }
    return true;
}

void getPlayerMove(int currentPlayer, int& row, int& col) {
    cout << "Player" << currentPlayer << " enter row and column (0-"
         << BOARD_SIZE - 1 << "): ";
    cin >> row >> col;
}

void makeMove(int row, int col, char playerSymbol) {
    board[row][col] = playerSymbol;
}

void startGame() {
    int currentPlayer = 1;
    bool gameWon = false;
    bool gameTied = false;
    while (!gameWon && !gameTied) {
        system("cls");
        printBoard();

        int row, col;
        getPlayerMove(currentPlayer, row, col);

        if (board[row][col] != EMPTY_CELL) {
            continue;
        }

        char playerSymbol =
            (currentPlayer == 1) ? PLAYER_1_SYMBOL : PLAYER_2_SYMBOL;
        makeMove(row, col, playerSymbol);

        if (checkWin(playerSymbol)) {
            gameWon = true;
            cout << "Player " << currentPlayer << " wins!" << endl;
        } else if (checkTie()) {
            gameTied = true;
            cout << "Game tied!" << endl;
        } else {
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }
    printBoard();
}

int main() {
    startGame();
    return 0;
}
