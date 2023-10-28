#include <bits/stdc++.h>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char PLAYER_1_SYMBOL = 'X';
const char PLAYER_2_SYMBOL = 'O';

int currentPlayer;
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

void multiMode() {
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
            return;
        } else if (checkTie()) {
            gameTied = true;
            cout << "Game tied!" << endl;
            return;
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

        //Count valid substring type 1 in current row
        int curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curRow.find(valid1,curIndex+1);
        }

        // Count valid substring type 2 in current row
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

        //Count valid substrings type 1 in current column
        int curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curColumn.find(valid1,curIndex+1);
        }

        // Count valid substrings type 2 in current column
        curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curColumn.find(valid2,curIndex+1);
        }
    }
    return cnt;
}

int countDiagonals(char c, int ignore) {
    int cnt = 0, validLength = 5 -  ignore;
    string valid1 = ".", valid2 = ".";
    for (int i = 0; i < validLength; i++) valid1 += c, valid2 = c + valid2;

    // Count the main diagonals
    for (int i = 0; i <= BOARD_SIZE - validLength; i++) {
        // Current main diagonal
        string curDiag = "";
        for (int j = 0; j < BOARD_SIZE - i; j++) {
            if (board[j][j + i] == c) curDiag += c;
            else curDiag += '.';
        }

        //Count valid substrings type 1 in current main diagonal
        int curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curDiag.find(valid1,curIndex+1);
        }

        // Count valid substrings type 2 in current main diagonal
        curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curDiag.find(valid2,curIndex+1);
        }
    }

    // Count the anti-diagonals
    for (int i = 0; i <= BOARD_SIZE - validLength; i++) {
        // Current anti-diagonal
        string curDiag = "";
        for (int j = 0; j < BOARD_SIZE - i; j++) {
            if (board[j][BOARD_SIZE - 1 - j - i] == c) curDiag += c;
            else curDiag += '.';
        }

        //Count valid substrings type 1 in current anti-diagonal
        int curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curDiag.find(valid1,curIndex+1);
        }

        // Count valid substrings type 2 in current anti-diagonal
        curIndex = 0;
        while (curIndex != string::npos) {
            cnt++;
            curIndex = curDiag.find(valid2,curIndex+1);
        }
    }
    return cnt;
}

int countAll(char c, int ignore) {
    return countRows(c,ignore)+countColumns(c,ignore)+countDiagonals(c,ignore);
}

// Evaluate score for each state of the game
double evaluateScore(char prevTurn) {
    int ignoreOne = countAll(prevTurn,1);
    int ignoreTwo = countAll(prevTurn,2);
    int ignoreThree = countAll(prevTurn,3);
    double score = ignoreOne*100.0+ignoreTwo*5.0+ignoreThree*1.0;
    return score;
}

vector<pair<int,int>> getPlaces(char c) {
    vector<pair<int,int>> ans;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
    if (board[i][j] == c) ans.push_back({i,j});
    return ans;
}

vector<pair<int,int>> availableMove(int i, int j) {
    vector<pair<int,int>> ans;
    // Define the possible directions as arrays of offsets
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int k = 0; k < 8; k++) {
        // Next pos
        int x = i + dx[k];
        int y = j + dy[k];
        // Check if the next position is valid
        if (x >= 0 && x < 10 && y >= 0 && y < 10 && board[x][y] == '.')
            ans.push_back({x, y});

    }
    return ans;
}

pair<double,pair<int,int>> minimax(int d, double alpha, double beta) {
    vector<pair<int,int>> moveList,places;
    set<pair<int,int>> uniqueMove;
    char cur = (currentPlayer == 1 ? 'O' : 'X');
    places = (getPlaces(cur));
    // Get all unique move for next player
    for (int i = 0; i < places.size(); i++) {
        vector<pair<int,int>> all = availableMove(places[i].first,places[i].second);
        for (auto x: all) uniqueMove.insert(x);
    }
    if (uniqueMove.empty()) {

    } else for (auto i: uniqueMove) moveList.push_back(i);
    //Minimax
    double bestScore;
    double tempScore;
    pair<int,int> bestMove;
    if (!d) return {evaluateScore(cur),moveList[0]};
    bestScore = alpha;
    while (!moveList.empty()) {

    }
    return {bestScore,bestMove};
}

void singleMode() {

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
        multiMode();
    }
    else singleMode();
    return;
}

signed main() {
    startGame();
    return 0;
}
