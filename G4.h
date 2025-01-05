#ifndef G4_H
#define G4_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>

template <typename T>
class words_board : public Board<T> {
public:
    words_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
private:
    set<std::string> words;
    void implementation();
};

template <typename T>
class words_Player : public Player<T> {
public:
    words_Player(std::string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class words_Random_Player : public RandomPlayer<T> {
public:
    words_Random_Player(T symbol);
    void getmove(int& x, int& y);
    char get_random_letter();
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

// Constructor for G4_Board
template <typename T>
words_board<T>::words_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    implementation();
    this->n_moves = 0;
}

template <typename T>
void words_board<T>::implementation() {
    ifstream file("dic.txt");

    if (!file) {
        cerr << "Error: Failed to open 'dic.txt'. Ensure the file exists in the program directory.\n";
        exit(1);
    }

    string word;
    while (file >> word) {
        words.insert(word);
    }
    file.close();
}

template <typename T>
bool words_board<T>::update_board(int x, int y, T Symbol) {

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(Symbol);
        return true;
    }
    return false;
}

template <typename T>
void words_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool words_board<T>::is_win() {
    string check, reversedCheck;

    for (int i = 0; i < this->rows; i++) {
        check = "";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0) {
                check += this->board[i][j];
            }
        }
        reversedCheck = check;
        reverse(reversedCheck.begin(), reversedCheck.end());
        if (check.length() == 3 && (words.find(check) != words.end() || words.find(reversedCheck) != words.end())) {
            return true;
        }
    }
    check.clear();

    for (int j = 0; j < this->columns; j++) {
        check = "";
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][j] != 0) {
                check += this->board[i][j];
            }
        }
        reversedCheck = check;
        reverse(reversedCheck.begin(), reversedCheck.end());
        if (check.length() == 3 && (words.find(check) != words.end() || words.find(reversedCheck) != words.end())) {
            return true;
        }
    }

    // diagonally
    check.clear();
    check += this->board[0][0];
    check += this->board[1][1];
    check += this->board[2][2];
    reversedCheck = check;
    reverse(reversedCheck.begin(), reversedCheck.end());
    if (check.length() == 3 && (words.find(check) != words.end() || words.find(reversedCheck) != words.end())) {
        return true;
    }

    check.clear();
    check += this->board[0][2];
    check += this->board[1][1];
    check += this->board[2][0];
    reversedCheck = check;
    reverse(reversedCheck.begin(), reversedCheck.end());
    if (check.length() == 3 && (words.find(check) != words.end() || words.find(reversedCheck) != words.end())) {
        return true;
    }

    return false;
}

template <typename T>
bool words_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool words_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
words_Player<T>::words_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void words_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << this->name << ", enter your move (row and column) separated by spaces: ";
        cin >> x >> y;
        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            cout << "Invalid position! Please enter values between 0 and 2.\n";
            continue;
        }

        char letter;
        cout << "Enter the letter to place:";
        cin >> letter;

        if (!isalpha(letter)) {
            cout << "Invalid letter! Please enter an alphabetic character.\n";
            continue;
        }

        this->symbol = toupper(letter);
        break;
    }
}

template <typename T>
words_Random_Player<T>::words_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player ";
    this->name += this->symbol;

    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void words_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = get_random_letter();

    cout << this->name << " places '" << this->symbol << "' at (" << x << ", " << y << ")." << endl;
}

template <typename T>
char words_Random_Player<T>::get_random_letter() {
    return 'A' + rand() % 26;
}
#endif

