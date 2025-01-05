#ifndef G6_H
#define G6_H

#include "BoardGame_Classes.h"
#include "bits/stdc++.h"
template <typename T>
class misere_board: public Board<T> {
public:
    static bool is_win_x,is_win_o,skip_round;
    misere_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void reset_static_variables();


};

template <typename T>
class misere_Player : public Player<T> {
public:
    misere_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class misere_Random_Player : public RandomPlayer<T>{
public:
    misere_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//-------------------------------------------------------------Implementation

//-------------------------------------------------------------Static variables
template <typename T>
bool misere_board<T>::is_win_x = false;

template <typename T>
bool misere_board<T>::is_win_o = false;

template <typename T>
bool misere_board<T>::skip_round = false;

//-------------------------------------------------------------Board
template <typename T>
misere_board<T>::misere_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    reset_static_variables();
}

template <typename T>
bool misere_board<T>::update_board(int x, int y, T symbol) {

    if(is_win_o || skip_round) return true;

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void misere_board<T>::display_board() {
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
void misere_board<T>::reset_static_variables() {
    is_win_x = false,is_win_o = false,skip_round = false;
}
template <typename T>
bool misere_board<T>::is_win() {
    if(is_win_o || skip_round)
        return true;
    if(is_win_x) {
        skip_round = true;
    }
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0){
            this->board[i][0] == 'X'? is_win_o = true : is_win_x = true;

        }
    }
    for (int i = 0; i < this->columns; ++i) {
        if(this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) {
            this->board[0][i] == 'X'? is_win_o = true : is_win_x = true;

        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        this->board[0][0] == 'X'? is_win_o = true : is_win_x = true;

    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool misere_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool misere_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
misere_Player<T>::misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void misere_Player<T>::getmove(int& x, int& y) {
    if(misere_board<T>::is_win_o || misere_board<T>::skip_round) return;

    cout << "Please enter your move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;


}

// Constructor for X_O_Random_Player
template <typename T>
misere_Random_Player<T>::misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player ";
    this->name += this->symbol;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void misere_Random_Player<T>::getmove(int& x, int& y) {
    if(misere_board<T>::is_win_o || misere_board<T>::skip_round) return;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //G6_H
