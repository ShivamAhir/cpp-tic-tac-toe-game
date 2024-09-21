#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to display the filled matrix
void showFilledMatrix(vector<pair<int, char> > pos) {
    cout << endl << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << pos[i].second << " | " << pos[i + 1].second << " | " << pos[i + 2].second
             << "\t\t\t\t" << i + 1 << " | " << i + 2 << " | " << i + 3 << endl;
    }
}

// Function to display the format of the input matrix
void showMatrix() {
    cout << "Choose the following format to enter input:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (3 * i + j + 1);
            if (j != 2) {
                cout << " | ";
            }
        }
        cout << endl;
    }
}

// Function to check if a player has won
bool checkWin(vector<pair<int, char> > &pos, char playerChar) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (pos[i].second == playerChar && pos[i + 1].second == playerChar && pos[i + 2].second == playerChar)
            return true;
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (pos[i].second == playerChar && pos[i + 3].second == playerChar && pos[i + 6].second == playerChar)
            return true;
    }
    // Check diagonals
    if ((pos[0].second == playerChar && pos[4].second == playerChar && pos[8].second == playerChar) ||
        (pos[2].second == playerChar && pos[4].second == playerChar && pos[6].second == playerChar))
        return true;

    return false;
}

// Function to check if the game is a draw
bool checkDraw(vector<pair<int, char> > &pos) {
    for (const auto &p : pos) {
        if (p.second == '-') {
            return false; // If there's an empty position, it's not a draw yet
        }
    }
    return true; // All positions are filled and no winner
}

int main() {
    string player1, player2;
    cout << "\t\t\t\t Welcome To The Game" << endl << endl;

    cout << "Enter player1 name: ";
    cin >> player1;

    cout << "Enter player2 name: ";
    cin >> player2;

    // Initialize a 3x3 grid with empty positions marked as '-'
    vector<pair<int, char> > pos(9, make_pair(0, '-'));

    // Display the format of the matrix
    showMatrix();

    int turn = 0; // Turn counter to alternate between players
    while (true) {
        // Determine the current player and character
        string currentPlayer = (turn % 2 == 0) ? player1 : player2;
        char playerChar = (turn % 2 == 0) ? 'X' : 'O';

        // Display the filled matrix before each turn
        if (turn != 0)
            showFilledMatrix(pos);

        // Prompt the current player for their move
        cout << currentPlayer << "'s turn: ";
        int move;
        cin >> move;

        // Check for invalid input
        if (move > 9 || move < 1) {
            cout << "Invalid input: Please enter correct input" << endl;
            continue;
        }

        // Check if the position is already occupied
        if (pos[move - 1].first != 0) {
            cout << "This position is occupied. Please choose another position." << endl;
            continue;
        }

        // Mark the position for the current player
        pos[move - 1].first = 1;
        pos[move - 1].second = playerChar;

        // Check for a win condition
        if (checkWin(pos, playerChar)) {
            showFilledMatrix(pos);
            cout << currentPlayer << " wins!" << endl;
            break;
        }

        // Check for a draw condition
        if (checkDraw(pos)) {
            showFilledMatrix(pos);
            cout << "The game is a draw!" << endl;
            break;
        }

        // Increment the turn counter to switch players
        turn++;
    }

    return 0;
}
