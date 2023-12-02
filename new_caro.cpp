#include <bits/stdc++.h>

using namespace std;

class Board {
   private:
    /* Define a game board
       0: Empty cell
       1: 'X' turn (White) (First player)
       2: 'O' turn (Black) (Second player) */
    vector<vector<int>> board;

   public:
    // Initialize new game board (constructor)
    Board(int szRow, int szCol) : board(szRow, vector<int>(szCol, 0)) {}

    // Deep copy a game board (copy constructor)
    Board(const Board &board) : board(board.getBoard()) {}

    int getBoardSize() const { return board.size(); }

    vector<vector<int>> getBoard() const { return board; }

    // Make the cell empty
    void removeMove(int x, int y) { board[x][y] = 0; }

    // Assign the value for each player's turn
    void addMove(int x, int y, bool isSecond) {
        board[x][y] = (isSecond ? 2 : 1);
    }

    // Check this cell empty or not, if empty -> assign the move
    bool isEmpty(int x, int y, bool isSecond) {
        if (board[x][y] != 0) return false;
        board[x][y] = (isSecond ? 2 : 1);
        return true;
    }

    // Count all empty cells has at least one non-empty adjacent cell
    vector<vector<int>> genMove() const {
        vector<vector<int>> moveList;
        int boardSize = board.size();
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] > 0) continue;
                //
                if (i > 0) {
                    if (j > 0)
                        if (board[i - 1][j - 1] > 0 || board[i][j - 1] > 0) {
                            moveList.push_back({i, j});
                            continue;
                        }
                    if (j < boardSize - 1)
                        if (board[i - 1][j + 1] > 0 || board[i][j + 1] > 0) {
                            moveList.push_back({i, j});
                            continue;
                        }
                    if (board[i - 1][j] > 0) {
                        moveList.push_back({i, j});
                        continue;
                    }
                }
                if (i < boardSize - 1) {
                    if (j > 0) {
                        if (board[i + 1][j - 1] > 0 || board[i][j - 1] > 0) {
                            moveList.push_back({i, j});
                            continue;
                        }
                    }
                    if (j < boardSize - 1) {
                        if (board[i + 1][j + 1] > 0 || board[i][j + 1] > 0) {
                            moveList.push_back({i, j});
                            continue;
                        }
                    }
                    if (board[i + 1][j] > 0) {
                        moveList.push_back({i, j});
                        continue;
                    }
                }
            }
        }
        return moveList;
    }
};

class Minimax {
   private:
    Board board;
    // Maximum score to gurantee this is instantly winning move
    static const int WIN_SCORE = 1e9;

   public:
    static int getWinScore() { return WIN_SCORE; }

    // Return the ability that second player can win first player
    static double evaluateSecondPlayerScore(Board &board, bool isSecond) {
        double firstPlayerScore = getScore(board, false, isSecond);
        double secondPlayerScore = getScore(board, true, isSecond);
        if (!secondPlayerScore) secondPlayerScore = 1.0;
        return firstPlayerScore / secondPlayerScore;
    }

    // Evaluate the score for specified player
    static getScore(Board &board, bool forSecond, bool isSecond) {
        int score = evaluateHorizontal(board.getBoard(), forSecond, isSecond) +
                    evaluateVertical(board.getBoard(), forSecond, isSecond) +
                    evaluateDiagonal(board.getBoard(), forSecond, isSecond);
        return score;
    }

    // Find the next move for bot
    int calcNextMove(int depth) {
        int move[2];
        move[0] = -1, move[1] = -1;
        // Check if any available instantly winning move
        pair<int, int> bestMove = searchWinningMove(board);
        if (bestMove.first != -1) {
            move[0] = bestMove.first;
            move[1] = bestMove.second;
        } else {
            // If there is no such move, use minimax to find
            bestMove =
                minimaxSearch(depth, Board(board), true, -1.0, getWinScore());
            if (bestMove[1] == -1)
                move = -1;
            else {
                move[0] = bestMove[1];
                move[1] = bestMove[2];
            }
        }
        return move;
    }

    /* alpha: best bot move
       beta: best player move
       return: {score,move[0],move[1]}
    */
    pair<int, int> minimaxSearch(int depth, Board tmpBoard, bool Max,
                                 double alpha, double beta) {
        // Base case, return the score and empty move
        if (!depth) {
            int res = new int[3];
            res[0] = evaluateSecondPlayerScore(tmpBoard, !Max);
            res[1] = -1;
            res[2] = -1;
            return res;
        }

        vector<int> allMove = tmpBoard.genMove();
        // If there is no such available move, consider this node like the base
        // case
        //  -> return the score and empty move
        if (!allMove.size()) {
            int res = new int[3];
            res[0] = evaluateFirstPlayerScore(tmpBoard, !Max);
            res[1] = -1;
            res[2] = -1;
            return res;
        }

        // Gen the minimax tree, calculate the score
        int bestMove = new int[3];
        if (Max) {
            // Initialize the initial best move is the lowest score
            bestMove[0] = -1.0;
            for (int i = 0; i < allMove.size(); i++) {
                tmpBoard.addStone(allMove[i][1], allMove[i][0], false);
                // Gen new minimax tree from current node
                // Search for the minimum score for each subtree of each nodes
                int tmpMove =
                    minimaxSearch(depth - 1, tmpBoard, false, alpha, beta);
                tmpBoard.removeMove(allMove[i][1], allMove[i][0]);
                // Update the alpha (maximum score)
                // If the score of current node is lower than alpha, the whole
                // subtree of this node will be ignored.
                if (tmpMove[0] > alpha) alpha = tmpMove[0];
                // Pruning with the beta (minimum score)
                // We need the score which is lower than current beta
                //-> if the score is higher or equal to current beta, ignore all
                //node and subtree and return the last move.
                if (tmpMove[0] >= beta) return tmpMove;
                // Find the move with maximum score
                if (tmpMove[0] > bestMove[0]) {
                    bestMove[0] = tmpMove[0];
                    bestMove[1] = allMove[i][0];
                    bestMove[2] = allMove[i][1];
                }
            }
        } else {
            // minimizing player
            // Initialize the initial best move is the highest score
            bestMove[0] = 1000000000.0;
            bestMove[1] = allMove[0][0];
            bestMove[2] = allMove[0][1];
            for (int i = 0; i < allMove.size(); i++) {
                tmpBoard.addStone(allMove[i][1], allMove[i][0], true);
                // Gen new minimax tree from current node
                // Search for the minimum score for each subtree of each nodes
                int tmpMove =
                    minimaxSearch(depth - 1, tmpBoard, true, alpha, beta)
                        tmpBoard.removeMove(allMove[i][1], allMove[i][0]);
                // Update the beta (minimum score)
                // If the score of current node is hgiher than beta, the whole
                // subtree of this node will be ignored.
                if (tmpMove[0] < beta) beta = tmpMove[0];
                // Pruning with alpha
                // We need the score which is hight than current alpha
                //-> if the score is lower or equal to current beta, ignore all
                //node and subtree and return the last move.
                if (tmpMove[0] <= alpha) return tmpMove;
                // Find the move with minimum score.
                if (tmpMove[0] < bestMove[0]) {
                    bestMove[0] = tmpMove[0];
                    bestMove[1] = allMove[i][0];
                    bestMove[2] = allMove[i][1];
                }
            }
        }
        return bestMove;
    }

    // Search for the instantly winning move
    pair<int, int> searchWinningMove(Board board) {
        vector<int> allMove = board.genMove();
        pair<int, int> winMove;
        for (int i = 0; i < allMove.size(); i++) {
            Board tmpBoard = board;
            tmpBoard.addMove(allMove[i][1], allMove[i][0], false);
            if (getScore(tmpBoard, false, false) >= WIN_SCORE) {
                winMove[0] = allMove[i][0];
                winMove[1] = allMove[i][1];
                return winMove;
            }
        }
        return {-1, -1};
    }

    static int evaluateHorizontal(vector<vector<int>> board, bool forSecond,
                                  bool curTurn) {
        // 0: consecutive count, 1: block count, 2: score
        int evalutions[3] = {0, 2, 0};
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                evaluateDirections(board, i, j, forSecond, curTurn, evalutions);
            }
            evaluateDirectionAfterOnePass(evalutions, forSecond, curTurn);
        }
        return evalutions[2];
    }

    static int evaluateVertical(vector<vector<int>> board, bool forSecond,
                                bool curTurn) {
        // 0: consecutive count, 1: block count, 2: score
        int evalutions[3] = {0, 2, 0};
        for (int j = 0; j < board.size(); j++) {
            for (int i = 0; i < board.size(); i++) {
                evaluateDirections(board, i, j, forSecond, playerTurn,
                                   evalutions);
            }
            evaluateDirectionAfterOnePass(evalutions, forSecond, curTurn);
        }
        return evalutions[2];
    }

    static int evaluateDiagonal(vector<vector<int>> board, bool forSecond,
                                bool curTurn) {
        // 0: consecutive count, 1: block count, 2: score
        int evalutions[3] = {0, 2, 0};
        // bottom-left to top-right
        for (int k = 0; k <= 2 * (board.size() - 1); k++) {
            int iStart = max(0, k - static_cast<int>(boardMatrix.size()) + 1);
            int iEnd = min(static_cast<int>(boardMatrix.size()) - 1, k);
            for (int i = iStart; i <= iEnd; ++i) {
                evaluateDirections(board, i, k - i, forSecond, curTurn,
                                   evaluations);
            }
            evaluateDirectionsAfterOnePass(evaluations, forSecond, curTurn);
        }

        // From top-left to bottom-right diagonally
        for (int k = 1 - static_cast<int>(board.size());
             k < static_cast<int>(board.size()); k++) {
            int iStart = max(0, k);
            int iEnd = min(static_cast<int>(board.size() + k - 1),
                           static_cast<int>(board.size()) - 1);
            for (int i = iStart; i <= iEnd; ++i) {
                evaluateDirections(board, i, i - k, forSecond, curTurn,
                                   evaluations);
            }
            evaluateDirectionsAfterOnePass(evaluations, forSecond, curTurn);
        }
        return evaluations[2];
    }

    static void evaluateDirections(vector<vector<int>> booard, int i, int j,
                                   bool isBot, bool botTurn, int eval[3]) {
        // Check if the selected player has a stone in the current cell
        // Increment consecutive stones count
        if (boardMatrix[i][j] == (isBot ? 2 : 1)) eval[0]++;
        // Check if cell is empty
        else if (boardMatrix[i][j] == 0) {
            // Check if there were any consecutive stones before this empty cell
            if (eval[0] > 0) {
                // Consecutive set is not blocked by the opponent, decrement
                // block count
                eval[1]--;
                // Get consecutive set score
                eval[2] +=
                    getConsecutiveSetScore(eval[0], eval[1], isBot == botsTurn);
                // Reset consecutive stone count
                eval[0] = 0;
                // Current cell is empty, next consecutive set will have at most
                // 1 blocked side.
            }
            // No consecutive stones.
            // Current cell is empty, next consecutive set will have at most 1
            // blocked side.
            eval[1] = 1;
        }
        // Cell is occupied by opponent
        // Check if there were any consecutive stones before this empty cell
        else if (eval[0] > 0) {
            // Get consecutive set score
            eval[2] +=
                getConsecutiveSetScore(eval[0], eval[1], isBot == botsTurn);
            // Reset consecutive stone count
            eval[0] = 0;
            // Current cell is occupied by the opponent, next consecutive set
            // may have 2 blocked sides
            eval[1] = 2;
        } else {
            // Current cell is occupied by the opponent, next consecutive set
            // may have 2 blocked sides
            eval[1] = 2;
        }
    }

    static void evaluateDirectionsAfterOnePass(int eval[3], bool isBot,
                                               bool playersTurn) {
        // End of row, check if there were any consecutive stones before
        // reaching the right border
        if (eval[0] > 0) {
            eval[2] +=
                getConsecutiveSetScore(eval[0], eval[1], isBot == playersTurn);
        }
        // Reset consecutive stone and blocks count
        eval[0] = 0;
        eval[1] = 2;
    }

    // cnt: Number of consecutive stones in the set
    // blocks: Number of blocked sides of the set (2: both sides blocked, 1:
    // single side blocked, 0: both sides free)
    static int getConsecutiveSetScore(int cnt, int blocks, bool curTurn) {
        const int winGuarantee = 1e9;
        // If both sides of a set are blocked and this set has less than 5
        // consecutive stones, it is worthless, return 0 points.
        if (blocks == 2 && count < 5) return 0;
        switch (count) {
            case 5:
                // 5 consecutive stones win the game
                return WIN_SCORE;
            case 4:
                // 4 consecutive stones in the user's turn guarantee a win.
                // (User can win the game by placing the 5th stone after the
                // set)
                if (curTurn)
                    return winGuarantee;
                else {
                    // Opponent's turn
                    // If neither side is blocked, 4 consecutive stones
                    // guarantee a win in the next turn. (Opponent can only
                    // place a stone that will block the remaining side,
                    // otherwise the game is lost in the next turn). So, a
                    // relatively high score is given for this set.
                    if (blocks == 0) return winGuarantee / 4;
                    // If only a single side is blocked, 4 consecutive stones
                    // limit the opponent's move (Opponent can only place a
                    // stone that will block the remaining side, otherwise the
                    // game is lost in the next turn). So, a relatively high
                    // score is given for this set.
                    else
                        return 200;
                }

            case 3:
                // 3 consecutive stones
                if (blocks == 0) {
                    // Neither side is blocked.
                    // If it's the current player's turn, a win is guaranteed in
                    // the next 2 turns. (User places another stone to make the
                    // set 4 consecutive, opponent can only block one side)
                    // However, the opponent may win the game in the next turn,
                    // therefore this score is lower than win guaranteed scores
                    // but still a very high score.
                    if (curTurn) return 50000;
                    // If it's the opponent's turn, this set forces the opponent
                    // to block one of the sides of the set. So, a relatively
                    // high score is given for this set.
                    else
                        return 200;
                } else {
                    // One of the sides is blocked.
                    // Playmaker scores
                    if (curTurn)
                        return 10;
                    else
                        return 5;
                }

            case 2:
                // 2 consecutive stones
                // Playmaker scores
                if (blocks == 0) {
                    if (curTurn)
                        return 7;
                    else
                        return 5;
                } else {
                    return 3;
                }

            case 1:
                return 1;
        }
        // More than 5 consecutive stones?
        return WIN_SCORE * 2;
    }
};

signed main() { return 0; }
