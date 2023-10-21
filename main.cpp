#include <bits/stdc++.h>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char PLAYER_1_SYMBOL = 'X';
const char PLAYER_2_SYMBOL = 'O';

vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY_CELL));

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
    cout << "Player " << currentPlayer << " enter row and column (0-"
         << BOARD_SIZE - 1 << "): ";
    cin >> row >> col;
}

void makeMove(int row, int col, char playerSymbol) {
    board[row][col] = playerSymbol;
}

void singleMode() {
    int currentPlayer = 1, playerChoice;
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

        char playerSymbol = (currentPlayer == 1 ? PLAYER_1_SYMBOL : PLAYER_2_SYMBOL);
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

int countRows(char c, int ignore) {
    int cnt = 0, validLength = 5 -  ignore;
    string valid1 = ".", valid2 = ".";
    for (int i = 0; i < validLength; i++) valid1 += c, valid2 = c + valid2;

    for (int i = 0; i < BOARD_SIZE; i++) {

        // Current row
        string curRow = "";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == c) curRow += c;
            else curRow += '.';
        }

        //Count valid substring 1 in current row
        int curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curRow.find(valid1,curIndex+1);
        }

        // Count valid substring 2 in current row
        curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curRow.find(valid2,curIndex+1);
        }
    }
    return cnt;
}

int countColumns(char c, int ignore) {
    int cnt = 0, validLength = 5 -  ignore;
    string valid1 = ".", valid2 = ".";
    for (int i = 0; i < validLength; i++) valid1 += c, valid2 = c + valid2;

    for (int i = 0; i < BOARD_SIZE; i++) {

        // Current column
        string curColumn = "";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[j][i] == c) curColumn += c;
            else curColumn += '.';
        }

        //Count valid substring 1 in current row
        int curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curColumn.find(valid1,curIndex+1);
        }

        // Count valid substring 2 in current row
        curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curColumn.find(valid2,curIndex+1);
        }
    }
    return cnt;
}

void multiMode() {

}

void startGame() {
    int playerChoice;
    cout << "Mode:\n";
    cout << "1. Single Player\n";
    cout << "2. Multi Player\n";
    cout << "Choose mode: ";
    cin >> playerChoice;
    if (playerChoice == 2) {
        system("cls");
        singleMode();
    }
    else multiMode();
}

signed main() {
    cout << countRows('X',1);
    //startGame();
    return 0;
}
