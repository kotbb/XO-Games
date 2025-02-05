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
    static vector <vector<bool>> positions;
    C4_board();
    bool update_board(int x, int y, T symbol);
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over() ;

    int check_move(int y, vector<vector<bool>> &vec);

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
        cout << "Please Enter the column you want to play, only the numbers of the column\n";
        cin >> y;
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
vector <vector<bool>> C4_board<T>::positions(6,vector<bool>(7,false));

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
    positions = vector<vector<bool>>(6, vector<bool>(7, false));
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

// to check if the column in the board is filled
template <typename T>
int C4_board <T> ::check_move(int y, vector<vector<bool>> &vec) {
    for (int i = 5; i >=0 ; i--) {
        if(!vec[i][y])
        {
            vec[i][y] = true;
            return i;
        }
    }
    return -1;
}

template <typename T>
bool C4_board<T> :: update_board(int x,int y, T symbol)
{
    bool is_random = false;
    if((symbol == 'x' || symbol == 'o'))
        is_random = true;
    if(y > 6)
    {
        cout << "Invalid input, choose column between (0 6)";
        return false;
    }
    x = check_move(y,positions);
    if(x == -1)
    {
        if(!is_random)
            cout << "You can't play here, the column is completely filled.\n";
        return false;
    }
    else
    {
        ++this->n_moves;
        this->board[x][y] = toupper(symbol);
        return true;
    }
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
                cout << " |  ";
            else
                cout << " | " << char(toupper(this->board[i][j]));
            if(j == 6)
                cout << " | ";
        }
        cout << endl;
        cout << string(30,'-') << endl;
    }
    for (int i = 0; i < 7 ; ++i) {
        cout << setw(4) << i;
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
    y = rand() % this->dimension;      // random(0,6)
}
#endif
