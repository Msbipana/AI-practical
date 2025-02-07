#include <iostream>
#include <climits>

using namespace std;

#define PLAYER 'X'  // The player maximizing the score
#define OPPONENT 'O'  // The opponent minimizing the score

// A function to check if a player has won
bool isWinning(char board[3][3], char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // Row
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) { // Column
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Diagonal
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) { // Anti-diagonal
        return true;
    }
    return false;
}

// A function to check if the board is full (no moves left)
bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                return false;
            }
        }
    }
    return true;
}

// A utility function to evaluate the board
int evaluate(char board[3][3]) {
    // Check for 'X' (Player) win
    if (isWinning(board, PLAYER)) {
        return +10;
    }
    // Check for 'O' (Opponent) win
    else if (isWinning(board, OPPONENT)) {
        return -10;
    }
    return 0; // No winner
}

// Min-Max algorithm to find the best move
int minMax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    // If 'X' wins, return +10
    if (score == 10) {
        return score;
    }
    // If 'O' wins, return -10
    if (score == -10) {
        return score;
    }
    // If no more moves can be made and it's a draw
    if (isBoardFull(board)) {
        return 0;
    }

    // If it's 'X' turn (maximize score)
    if (isMax) {
        int best = -INT_MAX;

        // Loop through all cells to find the best move
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    // Make the move
                    board[i][j] = PLAYER;
                    // Call Min-Max recursively and choose the maximum value
                    best = max(best, minMax(board, depth + 1, !isMax));
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    // If it's 'O' turn (minimize score)
    else {
        int best = INT_MAX;

        // Loop through all cells to find the best move
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    // Make the move
                    board[i][j] = OPPONENT;
                    // Call Min-Max recursively and choose the minimum value
                    best = min(best, minMax(board, depth + 1, !isMax));
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// A function to find the best move for the player
void findBestMove(char board[3][3]) {
    int bestVal = -INT_MAX;
    int row = -1, col = -1;

    // Loop through all cells to find the best move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                // Make the move
                board[i][j] = PLAYER;
                // Compute the evaluation function for this move
                int moveVal = minMax(board, 0, false);
                // Undo the move
                board[i][j] = '_';

                // If the value of the current move is more than the best value, update the best move
                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    // Output the best move
    cout << "The best move for 'X' is: " << endl;
    cout << "Row: " << row << ", Column: " << col << endl;
}

int main() {
    // Sample game board
    char board[3][3] = {
        {'X', 'O', 'X'},
        {'_', 'O', '_'},
        {'_', '_', '_'}
    };

    cout << "Initial board state: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    // Find the best move for the current player ('X')
    findBestMove(board);

    return 0;
}

