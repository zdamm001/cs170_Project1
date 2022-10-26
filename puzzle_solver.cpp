#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

struct index {
    int row = -1;
    int column = -1;
    index() {};
    index(int r, int c) : row(r), column(c) {}
};

class node {
 private:
    int gn; 
    int hn; 
    index blank;
 public:
    node(vector<vector<int>> s) : state(s) {};
    int get_fn() const {return gn + hn;} //estimated cost of the cheapest solution that goes through node n
    int get_gn() const {return gn;} //the cost to get to a node
    int get_hn() const {return hn;} //the estimated distance to the goal
    index get_blank() const {return blank;}
    void set_gn(int g) {gn = g;}
    void set_hn(int h) {hn = h;}
    void set_blank(int r, int c) {blank = {r, c};}
    string to_string() {string n; for (const auto& row : state) for (const auto& elem : row) n.push_back(elem + 0x30); return n;}
    void print() {for (const auto& row : state) {cout << '['; for (unsigned i = 0; i < row.size() - 1; ++i) cout << row[i] << ", "; cout << row[row.size() - 1] << "]\n";}}
    vector<vector<int>> state;
};

bool operator<(const node& lhs, const node& rhs) {
    return lhs.get_fn() < rhs.get_fn();
}

bool is_goal_state(const node& state) {
    for (unsigned i = 0; i < state.state.size(); ++i) {
        for (unsigned j = 0; j < state.state.size(); ++j) {
            if (state.state[i][j] != i * state.state.size() + j + 1) {
                if (state.state[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

vector<node> expand(node& curr_state, priority_queue<node>& nodes, map<string, bool>& explored_states) {
    int row = curr_state.get_blank().row;
    int column = curr_state.get_blank().column;
    vector<node> new_nodes;
    explored_states[curr_state.to_string()] = true;
    if (curr_state.get_blank().row != 0) {
        node new_state_up(curr_state.state);
        new_state_up.state[row][column] = new_state_up.state[row - 1][column];
        new_state_up.state[row - 1][column] = '0';
        new_state_up.set_blank(row - 1, column);
        if (explored_states[new_state_up.to_string()] == false) {
            new_nodes.push_back(new_state_up);
        }
    }
    if (curr_state.get_blank().row != curr_state.state.size() - 1) {
        node new_state_down(curr_state.state);
        new_state_down.state[row][column] = new_state_down.state[row + 1][column];
        new_state_down.state[row + 1][column] = '0';
        new_state_down.set_blank(row + 1, column);
        if (explored_states[new_state_down.to_string()] == false) {
            new_nodes.push_back(new_state_down);
        }
    }
    if (curr_state.get_blank().column != 0) {
        node new_state_left(curr_state.state);
        new_state_left.state[row][column] = new_state_left.state[row][column - 1];
        new_state_left.state[row][column - 1] = '0';
        new_state_left.set_blank(row, column - 1);
        if (explored_states[new_state_left.to_string()] == false) {
            new_nodes.push_back(new_state_left);
        }
    }
    if (curr_state.get_blank().column != curr_state.state.size() - 1) {
        node new_state_right(curr_state.state);
        new_state_right.state[row][column] = new_state_right.state[row][column + 1];
        new_state_right.state[row][column + 1] = '0';
        new_state_right.set_blank(row, column + 1);
        if (explored_states[new_state_right.to_string()] == false) {
            new_nodes.push_back(new_state_right);
        }
    }
    return new_nodes;
}

int misplaced_tile(node& curr_node) {
    int num_misplaced = 0;
    for (int i = 0; i < curr_node.state.size(); ++i) {
        for (int j = 0; j < curr_node.state.size(); ++j) {
            num_misplaced += curr_node.state[i][j] != (i * curr_node.state.size() + j + 1);
        }
    }
    return num_misplaced - 1;
}

int manhattan_distance(node& curr_node) {
    int total_manhattan = 0;
    for (int i = 0; i < curr_node.state.size(); ++i) {
        for (int j = 0; j < curr_node.state.size(); ++j) {
            if (curr_node.state[i][j]) {
                total_manhattan += i - ((curr_node.state[i][j] - 1) / curr_node.state.size());
                total_manhattan += j - ((curr_node.state[i][j] - 1) % curr_node.state.size());
            }
        }
    }
    return total_manhattan;
}

void a_star_search(priority_queue<node>& nodes, vector<node>& new_nodes, int heuristic) {
    for (unsigned i = 0; i < new_nodes.size(); ++i) {
        new_nodes[i].set_gn(new_nodes[i].get_gn() + 1);
        if (heuristic == 2) {
            new_nodes[i].set_hn(misplaced_tile(new_nodes[i]));
        }
        else if (heuristic == 3) {
            new_nodes[i].set_hn(manhattan_distance(new_nodes[i]));
        }
        else {
            new_nodes[i].set_hn(0);
        }
        nodes.push(new_nodes[i]);
    }
}

void general_search(vector<vector<int>>& puzzle, int heuristic) {
    priority_queue<node> nodes;
    node initial_state(puzzle);
    initial_state.set_gn(0);
    initial_state.set_hn(0);
    for (int i = 0; i < puzzle.size(); ++i) {
        for (int j = 0; j < puzzle.size(); ++j) {
            if (puzzle[i][j] == 0) {
                initial_state.set_blank(i, j);
                break;
            }
        }
    }
    nodes.push(initial_state);
    unsigned max_queue_size = 1;
    unsigned nodes_expanded = 0;
    map<string, bool> explored_states;
    while(true) {
        if (nodes.empty()) {
            cout << "Error: No solution found!" << endl;
            cout << "Number of nodes expanded: " << nodes_expanded << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            return;
        }
        if (nodes.size() > max_queue_size) {
            max_queue_size = nodes.size();
        }
        node curr_state = nodes.top();
        nodes.pop();
        if (is_goal_state(curr_state)) {
            cout << "\nGoal state!\n" << endl;
            cout << "Solution depth was " << curr_state.get_gn() << endl;
            cout << "Number of nodes expanded: " << nodes_expanded << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            return;
        }
        cout << "The best state to expand with a g(n) = " << curr_state.get_gn() << " and h(n) = " << curr_state.get_hn() << " is..." << endl;
        curr_state.print();
        vector<node> new_nodes = expand(curr_state, nodes, explored_states);
        a_star_search(nodes, new_nodes, heuristic);
        ++nodes_expanded;
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