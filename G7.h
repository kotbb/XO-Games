
#ifndef G7_H
#define G7_H

#include "BoardGame_Classes.h"
#include "bits/stdc++.h"
using namespace std;

template <typename T>
class X_O_4x4_Board:public Board<T> {
public:
    static vector<pair<int,int>> xPos_vec;
    static vector<pair<int,int>> oPos_vec;
    X_O_4x4_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void choose_move(int sym_x,int sym_y,int &xto,int &yto,bool is_random,T symbol);
    bool check_move(int x,int y, int move_x, int move_y,T symbol);
    int getPos(int x,int y,T symbol);
    vector<pair<int,int>> generate_possible_moves(int sym_x,int sym_y,T symbol);
};

template <typename T>
class X_O_4x4_Player : public Player<T> {
public:
    X_O_4x4_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class X_O_4x4_Random_Player : public RandomPlayer<T>{
public:
    X_O_4x4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//------------------------------------------------ Static members implementation
// this vectors to has the position of the existing X and O in the game.
template<typename T>
vector<pair<int,int>> X_O_4x4_Board<T>::xPos_vec(0);

template<typename T>
vector<pair<int,int>> X_O_4x4_Board<T>::oPos_vec(0);

//------------------------------------------------------ Board Implementation
template <typename T>
X_O_4x4_Board<T>::X_O_4x4_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    oPos_vec.clear();
    xPos_vec.clear();
    this->n_moves = 0;
    // to enter the place of each X and O in their vectors positions
    for (int j = 0; j < 4; ++j) {
        if(j % 2 == 0) {
            this->board[0][j] = 'O';
            oPos_vec.emplace_back(0,j);
        }
        else {
            xPos_vec.emplace_back(0,j);
            this->board[0][j] = 'X';
        }
    }
    for (int j = 0; j < 4; ++j) {
        if(j % 2 == 0) {
            xPos_vec.emplace_back(3,j);
            this->board[3][j] = 'X';
        }
        else {
            oPos_vec.emplace_back(3,j);
            this->board[3][j] = 'O';
        }
    }

}
// to return the place of X or O in their vector
template<typename T>
int X_O_4x4_Board<T>::getPos(int x,int y,T symbol) {
    bool isX = false;
    auto p = make_pair(x,y);
    if(symbol == 'X')
        isX = true;
    for (int i = 0; i < 8; ++i) {
        if(isX) {
            if(p == xPos_vec[i])
                return i;
        }
        else {
            if(p == oPos_vec[i])
                return i;
        }
    }
    return 0;
}
// to generate all possible moves for the X or O that the random will play with to make the code faster
template <typename T>
vector<pair<int,int>>X_O_4x4_Board<T>::generate_possible_moves(int sym_x,int sym_y,T symbol) {
    vector<pair<int,int>> vec;
    if(check_move(sym_x,sym_y,sym_x,sym_y+1,symbol)) {
        vec.emplace_back(sym_x,sym_y+1);
    }
    if(check_move(sym_x,sym_y,sym_x,sym_y-1,symbol)) {
        vec.emplace_back(sym_x,sym_y-1);
    }
    if(check_move(sym_x,sym_y,sym_x+1,sym_y,symbol)) {
        vec.emplace_back(sym_x+1,sym_y);
    }
    if(check_move(sym_x,sym_y,sym_x-1,sym_y,symbol)) {
        vec.emplace_back(sym_x-1,sym_y);
    }
    return vec;
}
// to choose the move of a human or random
template <typename T>
void X_O_4x4_Board<T>::choose_move(int x,int y,int &xto,int &yto,bool is_random,T symbol) {
    if(!is_random) {

        cout << "Please enter your move x and y (0 to 3) separated by spaces:";
        cin >> xto >> yto;
    }
    else {
        srand(static_cast<unsigned int>(time(0)));
        vector<pair<int,int>> possible_moves = generate_possible_moves(x, y,symbol); // to generate all posible moves for this X or O
        int size = possible_moves.size();
        if(size == 0) {         // this indicates that this symbol cannot move anywhere
            xto = 10;
            yto = 10;
            return;
        }
        // here to choose random move from the vector possible moves
        int ran_pos = rand() % size;
        xto = possible_moves[ran_pos].first;
        yto = possible_moves[ran_pos].second;
    }
}
// Display the board and the pieces on it
template <typename T>
void X_O_4x4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if(this->board[i][j] == 0)
                cout << " |  " << i << "," << j << " " << "   ";
            else
                cout << " |  "<< i << "," << j << "  "<< char(toupper(this->board[i][j])) << " ";
        }
        cout << endl;
        cout << string(45,'-') << endl;
    }
    cout << endl;
}
template <typename T>
bool X_O_4x4_Board<T>::update_board(int x, int y, T symbol) {
    bool is_random = false;
    if(symbol == 'x' || symbol == 'o')    // to check it is random or player
        is_random = true;

    int xto,yto;
    //to choose the place you want to play, if it is player and if it is random: make a random move
    choose_move(x,y,xto,yto,is_random,symbol);
    cin.clear();

    // to check the move is valid or not
    if(!check_move(x,y,xto,yto,symbol)) {
        if(!is_random)
            cout << "Invalid Choice...\n";
        return false;
    }
    // to update board with the new position move of the symbol and to update the vector places of the symbol
    symbol = toupper(symbol);
    int pos = getPos(x,y,symbol);
    this->board[x][y] = 0;
    this->board[xto][yto] = symbol;
    if(symbol == 'X') {             // here to update the positions of the new symbols moves
        xPos_vec[pos].first = xto;
        xPos_vec[pos].second = yto;
    }
    else {
        oPos_vec[pos].first = xto;
        oPos_vec[pos].second = yto;
    }
    return true;
}
// Returns true if there is any winner
template <typename T>
bool X_O_4x4_Board<T>::is_win() {
    // horizontally
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < 2; ++j) {
            if(this->board[i][j] == this->board[i][j+1] &&
               this->board[i][j+1] == this->board[i][j+2] &&
               this->board[i][j] != 0)
                return true;
        }
    }
    // vertically
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if(this->board[i][j] == this->board[i+1][j] &&
              this->board[i+1][j] == this->board[i+2][j] &&
              this->board[i][j] != 0)
                return true;
        }
    }

    // left to right
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (this->board[i][j] == this->board[i+1][j+1] &&
                this->board[i+1][j+1] == this->board[i+2][j+2] &&
                this->board[i][j] != 0)
                return true;
        }
    }

    // right to left
    for (int i = 0; i < 2; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[i][j] == this->board[i+1][j-1] &&
                this->board[i+1][j-1] == this->board[i+2][j-2] &&
                this->board[i][j] != 0)
                return true;
        }
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_4x4_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool X_O_4x4_Board<T>::game_is_over() {
    if(is_win() || is_draw()) {
        oPos_vec.clear();
        xPos_vec.clear();
        return true;
    }
    return false;
}
template <typename T>
bool X_O_4x4_Board<T>::check_move(int sym_x,int sym_y, int move_x, int move_y,T symbol) {
    symbol = toupper(symbol);
    // check if the move x or y is out of bounds
    if((move_x < 0 || move_x > 3) || (move_y < 0 || move_y > 3))
        return false;
    // check if the pos of the existed X or O isn't empty and the move pos is empty
    if(this->board[move_x][move_y] != 0 || this->board[sym_x][sym_y] != symbol) {
        return false;
    }
    // check if the moving position is adjacent
    if( (sym_x == move_x && (move_y == sym_y +1 || move_y == sym_y - 1)) || (sym_y == move_y && (move_x == sym_x +1 || move_x == sym_x - 1)))
    {
        return true;
    }
    return false;
}
//--------------------------------------------------- Player Implementation

// Constructor for X_O_Player
template <typename T>
X_O_4x4_Player<T>::X_O_4x4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_4x4_Player<T>::getmove(int& x, int& y) {
    cout << "Enter the place of " << this->symbol << " you want to move from separeted by space:";
    cin >> x >> y;
}
// Constructor for X_O_Random_Player
template <typename T>
X_O_4x4_Random_Player<T>::X_O_4x4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player ";
    this->name += this->symbol;
    srand(static_cast<unsigned int>(time(0)));

}

template <typename T>
void X_O_4x4_Random_Player<T>::getmove(int& x, int& y) {
    // to have a random place of the existing X or O in the game.
    int pos = rand() % this->dimension; // 0 to 4
    if(this->symbol == 'x') {
        x = X_O_4x4_Board<T>::xPos_vec[pos].first;
        y = X_O_4x4_Board<T>::xPos_vec[pos].second;
    }
    else {
        x = X_O_4x4_Board<T>::oPos_vec[pos].first;
        y = X_O_4x4_Board<T>::oPos_vec[pos].second;
    }
}
#endif //G7_H
