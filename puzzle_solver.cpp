#include <iostream>
#include <vector>

using namespace std;

void general_search() {

}

int main() {
    cout << "Welcome to my 8-Puzzle Solver." << endl;
    cout << "Type '1' to use a default puzzle, or '2' to create your own." << endl;

    int choice;
    cin >> choice;

    int eight_puzzle_size = 3;
    vector<vector<int>> puzzle(eight_puzzle_size, vector<int>(eight_puzzle_size));

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
        cout << "Enter the first row, using space between the numbers" << endl;
        cin >> puzzle[0][0] >> puzzle[0][1] >> puzzle[0][2];
        cout << "Enter the second row, using space between the numbers" << endl;
        cin >> puzzle[1][0] >> puzzle[1][1] >> puzzle[1][2];
        cout << "Enter the third row, using space between the numbers" << endl;
        cin >> puzzle[2][0] >> puzzle[2][1] >> puzzle[2][2];
    }
    return 0;
}

/*
function general-search(problem, QUEUEING-FUNCTION) 
nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE)) 
loop do
if EMPTY(nodes) then return "failure" 
 node = REMOVE-FRONT(nodes) 
if problem.GOAL-TEST(node.STATE) succeeds then return node
 nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS)) 
end
*/