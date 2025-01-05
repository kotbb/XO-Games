#ifndef G1_H
#define G1_H

#include "bits/stdc++.h"
#include "BoardGame_Classes.h"
using namespace std;

// ----------------------------------- pyramid_Board
template <typename T>
class pyramid_Board : public Board<T> {
public:
    pyramid_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    bool check_horizontal();
    bool check_vertical();
    bool check_diagonal();
};

// ----------------------------------- pyramid Player
template <typename T>
class pyramid_Player : public Player<T> {
public:
    pyramid_Player(string n, T symbol);
    pyramid_Player(T symbol);
    void getmove(int& x, int& y);
};

// ----------------------------------- pyramid Random Player
template <typename T>
class pyramid_Random_Player : public RandomPlayer<T> {
public:
    pyramid_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------- pyramid_board Implementation
template <typename T>
pyramid_Board<T>::pyramid_Board() {
    this->rows = 3;
    this->columns = 5; // Maximum number of columns for the largest row
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[i * 2 + 1];  // Adjust columns dynamically for pyramid shape
        for (int j = 0; j < i * 2 + 1; ++j) {
            this->board[i][j] = ' '; // Initialize with empty spaces
        }
    }
}

// Method to update the board with the player's symbol
template <typename T>
bool pyramid_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y > x * 2 || this->board[x][y] != ' ') {
        return false; // Invalid move
    }
    this->board[x][y] = symbol;
    return true;
}

// Method to display the board
template <typename T>
void pyramid_Board<T>::display_board() {
    vector<int> spaces = {13, 7, 1};
    vector<int> lines = {12, 24, 34};
    vector<int> spaces_lines = {11, 5, 1};


    for (int i = 0; i < this->rows; ++i) {
        cout << string(spaces[i], ' ');
        for (int j = 0; j <= i * 2; ++j) {

            if(this->board[i][j] == ' ')
                cout << "| " << i << "," << j << " ";
            else
                cout << "|  " << this->board[i][j] << "  ";
        }
        cout << "|" << endl;
        cout << string(spaces_lines[i], ' ') << string(lines[i], '-') << endl;
    }
    cout << endl;
}

// Method to check if there is a winner
template <typename T>
bool pyramid_Board<T>::is_win() {
    return check_horizontal() || check_vertical() || check_diagonal();
}

template <typename T>
bool pyramid_Board<T>::check_horizontal() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= i * 2 - 2; ++j) {
            if (this->board[i][j] != ' ' && this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool pyramid_Board<T>::check_vertical() {
    for (int i = 0; i < this->rows - 2; ++i) {
        for (int j = 0; j <= i * 2; ++j) {
            if (this->board[i][j] != ' ' && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool pyramid_Board<T>::check_diagonal() {
    return ((this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[0][0] != ' ') ||
            (this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[0][0] != ' '));
}

// Method to check if the game is a draw
template <typename T>
bool pyramid_Board<T>::is_draw() {
    if (is_win()) {
        return false;
    }

    int filledCells = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= i * 2; ++j) {
            if (this->board[i][j] != ' ') {
                filledCells++;
            }
        }
    }
    return filledCells == 9;
}

// Method to check if the game is over (either win or draw)
template <typename T>
bool pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------- pyramid_player Implementation
template <typename T>
pyramid_Player<T>::pyramid_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
pyramid_Player<T>::pyramid_Player(T symbol) : Player<T>(symbol) {}

template <typename T>
void pyramid_Player<T>::getmove(int& x, int& y) {
    cout << "Enter row (0-2):";
    cin >> x;
    cout << "Enter column (0-" << x * 2 << "):";
    cin >> y;
    cout << endl;
}

//--------------------------------- pyramid_random_player Implementation
template <typename T>
pyramid_Random_Player<T>::pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player ";
    this->name += this->symbol;

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void pyramid_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % (x * 2 + 1);  // Random column for the row based on pyramid shape
}

#endif
