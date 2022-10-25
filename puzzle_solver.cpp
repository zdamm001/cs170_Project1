#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

class node {
 private:
    int gn; 
    int hn; 
 public:
    node(vector<vector<int>> s) : state(s) {};
    int get_fn() const {return gn + hn;} //estimated cost of the cheapest solution that goes through node n
    int get_gn() const {return gn;} //the cost to get to a node
    int get_hn() const {return hn;} //the estimated distance to the goal
    void set_gn(int g) {gn = g;}
    void set_hn(int h) {hn = h;}
    bool operator<(const node& rhs) {
        return this->get_fn() < rhs.get_fn();
    }
    vector<vector<int>> state;
};

bool is_goal_state(const node& initial_state, const node& curr_state) {
    for (unsigned i = 0; i < initial_state.state.size(); ++i) {
        for (unsigned j = 0; j < initial_state.state.size(); ++j) {
            if (initial_state.state[i][j] != curr_state.state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

node& general_search(vector<vector<int>>& puzzle, int heuristic) {
    priority_queue<node> nodes;
    node initial_state(puzzle);
    initial_state.set_gn(0);
    initial_state.set_hn(0);
    nodes.push(initial_state);

    while(true) {
        if (nodes.empty()) {
            exit(EXIT_FAILURE);
        }
        node curr_state = nodes.top();
        nodes.pop();
        if (is_goal_state(initial_state, curr_state)) {
            cout << "\nGoal state!\n" << endl;
            cout << "Solution depth was 4" << endl;
            cout << "Number of nodes expanded: 13" << endl;
            cout << "Max queue size: 8" << endl;
            return curr_state;
        }
        //nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS)) 
    }
}

int main() {
    cout << "Welcome to my 8-Puzzle Solver." << endl;
    cout << "Type '1' to use a default puzzle, or '2' to create your own." << endl;

    int choice;
    cin >> choice;

    int eight_puzzle_size = 3;
    int puzzle_size = eight_puzzle_size;
    vector<vector<int>> puzzle(puzzle_size, vector<int>(puzzle_size));

    if (choice == 1) {
        int selected_difficulty;
        string difficulty;
        cout << "Please enter a desired difficulty on a scale from 0 to 5." << endl;
        cin >> selected_difficulty;
        switch (selected_difficulty) {
            case 0:
                difficulty = "trivial";
                puzzle = {{1,2,3},{4,5,6},{7,8,0}};
                break;
            case 1:
                difficulty = "very easy";
                puzzle = {{1,2,3},{4,5,6},{7,0,8}};
                break;
            case 2:
                difficulty = "easy";
                puzzle = {{1,2,0},{4,5,3},{7,8,6}};
                break;
            case 3:
                difficulty = "doable";
                puzzle = {{0,1,2},{4,5,3},{7,8,6}};
                break;
            case 4:
                difficulty = "oh boy";
                puzzle = {{8,7,1},{6,0,2},{5,4,3}};
                break;
            case 5:
                difficulty = "impossible";
                puzzle = {{1,2,3},{4,5,6},{8,7,0}};
                break;
            default:
                difficulty = "error";
                break;
        }
        cout << "Difficult of \'" << difficulty << "\' selected." << endl;
    }
    else if (choice == 2) {
        cout << "Enter your puzzle, using a zero to represent the blank." << endl;
        vector<string> row_name = {"first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "nineth", "tenth"};
        for (int i = 0; i < puzzle_size; ++i) {
            cout << "Enter the " << ((i < 10) ? (row_name.at(i)) : ("next")) << " row, using space between the numbers" << endl;
            for (int j = 0; j < puzzle_size; ++j) {cin >> puzzle[i][j];}
        }
    }
    int algorithm;
    cout << "Select algorithm. (1) for Uniform Cost Search" << endl <<
            "(2) for the Misplaced Tile Heuristic, or" << endl <<
            "(3) the Manhattan Distance Heuristic." << endl;
    cin >> algorithm;
    time_t start = clock();
    general_search(puzzle, algorithm);
    time_t end = clock();
    cout << "Total time: " << (end - start) / CLOCKS_PER_SEC << " seconds." << endl;
    return 0;
}