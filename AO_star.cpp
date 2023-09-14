#include <bits/stdc++.h>
using namespace std;

// Define a structure to represent the state of the problem
struct State {
    int x, y; // Monkey's position
    int crate_x, crate_y; // Crate's position
    int cost; // Total cost to reach this state

    // Define a constructor for convenience
    State(int x, int y, int crate_x, int crate_y, int cost)
        : x(x), y(y), crate_x(crate_x), crate_y(crate_y), cost(cost) {}

    // Define a comparison operator for the priority queue
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

// Define a function to calculate the heuristic (estimated) cost from a state to the goal
int heuristic(const State& current, const State& goal) {
    return abs(current.x - goal.x) + abs(current.y - goal.y);
}

// Define a function to perform A* search
int monkeyBananaAStar(int start_x, int start_y, int goal_x, int goal_y) {
    // Initialize the start and goal states
    State start_state(start_x, start_y, start_x, start_y, 0);
    State goal_state(goal_x, goal_y, goal_x, goal_y, 0);

    // Create a priority queue for the open set
    priority_queue<State, vector<State>, greater<State>> open_set;

    // Create a 2D array to keep track of visited states and their costs
    const int MAX_X = 10; // Adjust this based on the problem size
    const int MAX_Y = 10; // Adjust this based on the problem size
    vector<vector<int>> visited(MAX_X, vector<int>(MAX_Y, INT_MAX));

    // Push the start state into the open set
    open_set.push(start_state);
    visited[start_x][start_y] = 0;

    // Define possible moves: up, down, left, right
    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    // Start the A* search
    while (!open_set.empty()) {
        // Get the state with the lowest cost from the open set
        State current = open_set.top();
        open_set.pop();

        // Check if we have reached the goal state
        if (current.x == goal_x && current.y == goal_y) {
            return current.cost;
        }

        // Generate and process successor states
        for (int i = 0; i < 4; i++) {
            int new_x = current.x + dx[i];
            int new_y = current.y + dy[i];

            // Check if the new position is valid
            if (new_x >= 0 && new_x < MAX_X && new_y >= 0 && new_y < MAX_Y) {
                int new_cost = current.cost + 1; // Cost to move to the new position

                // If the monkey is at the same position as the crate, add an additional cost
                if (new_x == current.crate_x && new_y == current.crate_y) {
                    new_cost += 1; // Cost to push the crate
                }

                // Check if the new state has a lower cost than the previously visited state
                if (new_cost < visited[new_x][new_y]) {
                    visited[new_x][new_y] = new_cost;
                    State successor(new_x, new_y, current.x, current.y, new_cost + heuristic(State(new_x, new_y, current.x, current.y, 0), goal_state));
                    open_set.push(successor);
                }
            }
        }
    }

    // If no solution is found
    return -1;
}

int main() {
    int start_x, start_y, goal_x, goal_y;
    cout << "Enter the starting position (x y): ";
    cin >> start_x >> start_y;
    cout << "Enter the goal position (x y): ";
    cin >> goal_x >> goal_y;

    int minCost = monkeyBananaAStar(start_x, start_y, goal_x, goal_y);
    
    if (minCost != -1) {
        cout << "Minimum cost to reach the bananas: " << minCost << endl;
    } else {
        cout << "No valid path to the bananas." << endl;
    }

    return 0;
}
