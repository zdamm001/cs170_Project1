#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

class node {
 private:
    int fn;
    int gn;
    int hn;
    vector<vector<int>> state;
 public:
    node(vector<vector<int>> s) : state(s) {};
    int get_fn() const {return fn;}
    int get_gn() const {return gn;}
    int get_hn() const {return hn;}
    void set_fn(int f) {fn = f;}
    void set_gn(int g) {gn = g;}
    void set_hn(int h) {hn = h;}
};

bool operator<(const node& lhs, const node& rhs) {
    return lhs.get_fn() < rhs.get_fn();
}

void general_search(vector<vector<int>>& puzzle, int heuristic) {
    priority_queue<node> nodes;
    node initial_state(puzzle);
    initial_state.set_gn(0);
    initial_state.set_hn(0);
    initial_state.set_fn(0);
    nodes.push(initial_state);

    while(true) {
        if (nodes.empty()) {
            exit(EXIT_FAILURE);
        }
        node curr = nodes.top();
        nodes.pop();
        //if goal state then print and exit
        //else nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS)) 
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