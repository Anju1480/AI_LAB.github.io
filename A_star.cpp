#include <bits/stdc++.h>
using namespace std;

class State {
public:
    vector<int> queens; // Stores the column positions of queens for each row
    int n;

    State(int n) : queens(n, -1), n(n) {}

    // Check if it's safe to place a queen in the current row and column
    bool isSafe(int row, int col) {
        for (int i = 0; i < row; ++i) {
            // Check for conflicts in the same column or diagonally
            if (queens[i] == col || abs(queens[i] - col) == row - i) {
                return false;
            }
        }
        return true;
    }
};

// A* algorithm to solve N-Queens using backtracking
bool solveNQueens(State& state, int row) {
    int n = state.n;

    if (row == n) {
        // All queens are placed successfully
        return true;
    }

    for (int col = 0; col < n; ++col) {
        if (state.isSafe(row, col)) {
            state.queens[row] = col; // Place a queen

            if (solveNQueens(state, row + 1)) {
                // If placing a queen leads to a solution in the next row, return true
                return true;
            }

            // If placing a queen does not lead to a solution, backtrack
            state.queens[row] = -1;
        }
    }

    // If no queen can be placed in this row, return false
    return false;
}

// Helper function to print the board
void printBoard(const vector<int>& queens) {
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    State state(n);

    if (solveNQueens(state, 0)) {
        cout << "Solution found:" << endl;
        printBoard(state.queens);
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
