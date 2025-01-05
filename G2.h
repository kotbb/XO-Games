/*
Name        : Mohamed Ahmed Kotb
Id          : 20230315
Describtion : Connect 4 game, Each player plays with X or O, and to win , the player should fill
              three horizontally, vertically, diagonally, and the player should fill the bottom
              one in the column to first to play the above.
*/

#ifndef GAMES_OOP_G2_H
#define GAMES_OOP_G2_H

#include "bits/stdc++.h"
#include "BoardGame_Classes.h"
using namespace std;
//--------------------------------------------- Headers
//--------------------------------------- C4 board
template <typename T>
class C4_board : public Board<T>{

public:
    static vector <pair<int,int>> positions;
    C4_board();
    bool update_board(int x, int y, T symbol);
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over() ;
    void generate_positions();
    bool check_move(int x, int y, vector<pair<int,int>> &vec);

};
//-------------------------------------------- C4 Player
template <typename T>
class C4_player  : public Player <T>{

public:
    C4_player(string n,T symbol);
    C4_player(T symbol);
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
    void getmove(int& x, int& y) ;
};
//--------------------------------------------- C4 Random Player
template <typename T>
class C4_Random_Player : public RandomPlayer<T>{
public:
    C4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//-------------------------------------------Implementation

//-------------------------------------------  Player
template <typename T>
C4_player <T> :: C4_player(string n , T symbol) : Player<T>(n,symbol){}

template <typename T>
C4_player<T> ::C4_player(T symbol):Player<T>(symbol) {}

template <typename T>
T C4_player <T> :: getsymbol(){
    return this->symbol;
}

template <typename T>
string C4_player <T> :: getname()
{
    return this->name;
}

template <typename T>
void C4_player <T>:: getmove(int &x, int &y)
{
    while (true){
        cout << "Please Enter the place you want to play. Two numbers with space like (0 1)\n";
        cin >> x >> y;
        if (cin.fail()) {
            cout << "Invalid input. Please enter numeric values." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
}
//-----------------------------------------------Board
template <typename T>
vector <pair<int,int>> C4_board<T>::positions;

// generate all the positions that the user can play
template <typename T>
void C4_board<T>::generate_positions()
{
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7 ; ++j) {
            positions.emplace_back(i,j);
        }
    }
}
template <typename T>
C4_board<T>::C4_board()
{
    this->rows = 6, this->columns = 7;
    this->board = new char* [this->rows];


    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;

}

template <typename T>
bool C4_board <T> :: is_draw()
{
    if(this->n_moves == 42)
        return true;
    return false;
}

template <typename T>
bool C4_board <T> :: is_win()
{
    // Vertically
    for (int i = 0; i <= this->rows - 4; i++)
    {
        for (int j = 0; j < this->columns ; j++)
        {
            if(this->board[i][j] ==  this->board[i+1][j] &&
            this->board[i+1][j] == this->board[i+2][j] &&
            this->board[i+2][j] == this->board[i+3][j] &&
            this->board[i][j] != 0)
            {
                return true;
            }
        }
    }
    // Horizontally
      for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j <= this->columns - 4; j++)
        {
           if(this->board[i][j] ==  this->board[i][j+1]&&
           this->board[i][j+1] == this->board[i][j+2] &&
           this->board[i][j+2] == this->board[i][j+3] &&
           this->board[i][j] != 0)
            {
                return true;
            }
        }
    }
    // Diagonally
    /*
    00 01 02 03 04 05 06
    10 11 12 13 14 15 16
    20 21 22 23 24 25 26
    30 31 32 33 34 35 36
    40 41 42 43 44 45 46
    50 51 52 53 54 55 56

    */
   // left right diagonal
    for (int i = 0; i <= this->rows - 4; i++)
    {
        for (int j = 0; j <= this->columns -4; j++)
        {
            if(this->board[i][j] == this->board[i+1][j+1] &&
            this->board[i+1][j+1] ==  this->board[i+2][j+2] &&
            this->board[i+2][j+2] == this->board[i+3][j+3] &&
            this->board[i][j] != 0)
                return true;
        }
    }
    // right left diagonal
     for (int i = 0; i <= this->rows - 4; i++)
    {
        for (int j = 3; j < this->columns ; j++)
        {
            if(this->board[i][j] == this->board[i+1][j-1]
            &&  this->board[i+1][j-1] ==  this->board[i+2][j-2]
            &&  this->board[i+2][j-2] == this->board[i+3][j-3]
            &&  this->board[i][j] != 0)
                return true;
        }
    }
    return false;
}

template <typename T>
bool C4_board <T> :: game_is_over()
{
    if(is_win() || is_draw())
        return true;
    return false;
}

// to check if the bottom column in the board is filled or not to check the validation of the move
template <typename T>
bool C4_board <T> ::check_move(int x, int y, vector<pair<int, int>> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        if(y == vec[i].second)
        {
            if(x == vec[i].first)
            {
                vec.erase(vec.begin()+i);
                i--;
            }
            if(x < vec[i].first)
                return false;
        }
    }
    return true;
}

template <typename T>
bool C4_board<T> :: update_board(int x,int y, T symbol)
{
    bool is_random = false;
    if((symbol == 'x' || symbol == 'o'))
        is_random = true;

    if(!check_move(x,y,positions))
    {
        if(!is_random)
            cout << "You can't play here, you have to fill the bottom one in the column first.\n";
        return false;
    }
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0))
    {
        ++this->n_moves;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    if(!is_random)
        cout << "Invalid choice...\n";
    return false;
}

template <typename T>
void C4_board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            cout << setw(2);
            if(this->board[i][j] == 0)
                cout << " | " << i << "," << j;
            else
                cout << " |  " << char(toupper(this->board[i][j])) << " ";
        }
        cout << endl;
        cout << string(42,'-') << endl;
    }
    cout << endl;
}
//--------------------------------------Random Player
template <typename T>
C4_Random_Player<T>::C4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;

    this->name = "Random Computer Player ";
    this->name += this->symbol;

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void C4_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % (this->dimension - 1);  // random(0,5)
    y = rand() % this->dimension;      // random(0,6)
}
#endif
