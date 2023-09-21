#include <iostream>
#include <vector>
#include <set>

using namespace std;

class JugState {
public:
    int jug1, jug2;

    JugState(int j1, int j2) : jug1(j1), jug2(j2) {}

    bool operator==(const JugState& other) const {
        return jug1 == other.jug1 && jug2 == other.jug2;
    }

    bool operator<(const JugState& other) const {
        return jug1 < other.jug1 || (jug1 == other.jug1 && jug2 < other.jug2);
    }
};

void printState(const JugState& state) {
    cout << "(" << state.jug1 << ", " << state.jug2 << ")";
}

bool isGoalState(const JugState& state, int target) {
    return state.jug1 == target || state.jug2 == target;
}

bool isVisited(const JugState& state, const set<JugState>& visited) {
    return visited.find(state) != visited.end();
}

bool waterJugDFS(int capacity1, int capacity2, int target, JugState currentState, set<JugState>& visited, vector<JugState>& path) {
    if (isGoalState(currentState, target)) {
        path.push_back(currentState);
        return true;
    }

    visited.insert(currentState);

    // Fill jug1
    if (currentState.jug1 < capacity1) {
        JugState nextState(capacity1, currentState.jug2);
        if (!isVisited(nextState, visited) && waterJugDFS(capacity1, capacity2, target, nextState, visited, path)) {
            path.push_back(currentState);
            return true;
        }
    }

    // Fill jug2
    if (currentState.jug2 < capacity2) {
        JugState nextState(currentState.jug1, capacity2);
        if (!isVisited(nextState, visited) && waterJugDFS(capacity1, capacity2, target, nextState, visited, path)) {
            path.push_back(currentState);
            return true;
        }
    }

    // Empty jug1
    if (currentState.jug1 > 0) {
        JugState nextState(0, currentState.jug2);
        if (!isVisited(nextState, visited) && waterJugDFS(capacity1, capacity2, target, nextState, visited, path)) {
            path.push_back(currentState);
            return true;
        }
    }

    // Empty jug2
    if (currentState.jug2 > 0) {
        JugState nextState(currentState.jug1, 0);
        if (!isVisited(nextState, visited) && waterJugDFS(capacity1, capacity2, target, nextState, visited, path)) {
            path.push_back(currentState);
            return true;
        }
    }

    // Pour from jug1 to jug2
    if (currentState.jug1 > 0 && currentState.jug2 < capacity2) {
        int pour = min(currentState.jug1, capacity2 - currentState.jug2);
        JugState nextState(currentState.jug1 - pour, currentState.jug2 + pour);
        if (!isVisited(nextState, visited) && waterJugDFS(capacity1, capacity2, target, nextState, visited, path)) {
            path.push_back(currentState);
            return true;
        }
    }

    // Pour from jug2 to jug1
    if (currentState.jug2 > 0 && currentState.jug1 < capacity1) {
        int pour = min(currentState.jug2, capacity1 - currentState.jug1);
        JugState nextState(currentState.jug1 + pour, currentState.jug2 - pour);
        if (!isVisited(nextState, visited) && waterJugDFS(capacity1, capacity2, target, nextState, visited, path)) {
            path.push_back(currentState);
            return true;
        }
    }

    return false;
}

void printSolution(const vector<JugState>& path) {
    cout << "Solution found:" << endl;
    for (int i = path.size() - 1; i >= 0; i--) {
        printState(path[i]);
        if (i > 0) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int main() {
    int capacity1 = 4;
    int capacity2 = 3;
    int target = 2;

    JugState initialState(0, 0);
    set<JugState> visited;
    vector<JugState> path;

    if (waterJugDFS(capacity1, capacity2, target, initialState, visited, path)) {
        printSolution(path);
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
