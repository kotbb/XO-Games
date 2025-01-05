/*
Name        : Mohamed Ahmed Kotb
Id          : 20230315
Describtion : Numeric X_O, Each player plays with even or odd numbers from 1 to 15 and the first to
              collect three numbers horizontally, vertically, diagonally equals to 15 win, Each player
              plays only with odd numbers or even , he cannot play with both of them.
*/
#ifndef GAMES_OOP_G5_H
#define GAMES_OOP_G5_H

#include "bits/stdc++.h"
#include "BoardGame_Classes.h"

using namespace std;
//----------------------------------- Headers

//------------------------------------- numeric Board
template <typename T>
class numeric_board: public Board<T> {
public:
    numeric_board();
    bool update_board(int x, int y, T symbol);
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over() ;
};
//----------------------------------------- numeric Player
template <typename T>
class numeric_player : public Player<T> {
public:
    static vector<int> even;
    static vector<int> odd;
    numeric_player(string n, T symbol);
    numeric_player(T symbol);
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
    void getmove(int &x, int &y) ;

};
//---------------------------------------- numberic Random Player
template <typename T>
class numeric_Random_Player : public RandomPlayer<T>{
public:
    numeric_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//------------------------------------------Implementation
//------------------------------------- Static members

// vectors that has even and odd numbers that the user can play with
template<typename T>
vector <int> numeric_player <T>::even = {2,4,6,8,10,12,14};

template<typename T>
vector <int> numeric_player <T>::odd = {1,3,5,7,9,11,13};

//-------------------------------------------Player
template<typename T>
numeric_player<T>::numeric_player(string n, T symbol) :Player<T>( n, symbol) {
    even = {2,4,6,8,10,12,14};
    odd = {1,3,5,7,9,11,13};
}

template<typename T>
numeric_player<T>::numeric_player( T symbol) :Player<T>(symbol) {}

template<typename T>
T numeric_player<T>::getsymbol() {
    return this->symbol;
}
template<typename T>
string numeric_player<T>::getname() {
    return this->name;
}

template<typename T>
void numeric_player<T>::getmove(int &x, int &y) {

    int num;
    sort(even.begin(),even.end());
    sort(odd.begin(),odd.end());
    while(true)
    {
        if(this->symbol % 2 != 0)
        {
            cout << "Enter these odd numbers only: (";
            for(auto i : odd)
            {
                cout << i << " ";
            }
            cout << ")" << endl;
            cin >> num;
            bool is_Found = false;
            for(int i = 0; i < odd.size(); i++)
            {
                if(num == odd[i])
                {
                    is_Found = true;
                    odd.erase(odd.begin()+i);
                    break;
                }
            }
            // if the number that the user choose not included in the vector numbers that the player can play with
            if(!is_Found)
            {
                cout << "Invalid choice....\n";
                continue;
            }
        }
        else if(this->symbol % 2 == 0)
        {
            cout << "Enter these even numbers only: (";
            for(auto i : even)
            {
                cout << i << " ";
            }
            cout << ")" << endl;
            cin >> num;
            bool is_Found = false;
            for(int i = 0; i < even.size(); i++)
            {
                if(num == even[i])
                {
                    is_Found = true;
                    even.erase(even.begin()+i);
                    break;
                }
            }
            if(!is_Found)
            {
                cout << "Invalid choice......\n";
                continue;
            }
        }
        break;
    }
    this->symbol = num;
    cout << "Please Enter the place you want to play. Two numbers with space like (0 1)\n";
    cin >> x >> y;

}

//-----------------------------------------Board

template<typename T>
numeric_board<T>::numeric_board() {
    this->rows = 3 , this->columns = 3;
    this->board = new int *[this->rows];

    for (int i = 0; i < this->rows ; i++) {

        this->board[i] = new int [this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;

}


template<typename T>
void numeric_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << setw(2);
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0) {
                cout << " | " << i  << "," << j;
            }
            else
                cout << " | " << setw(3) << this->board[i][j]  ;
        }
        cout << endl;
        cout << string(20,'-') << endl;
    }
    cout << endl;
}
template <typename T>
bool numeric_board <T> :: update_board(int x, int y, T symbol) {
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0))
    {
        ++this->n_moves;
        this->board[x][y] = symbol;
        return true;
    }
    // to return the number that user take because it isnot valid
    if(symbol % 2 == 0)
        numeric_player<T>::even.push_back(symbol);
    else
        numeric_player<T>::odd.push_back(symbol);

    return false;
}


template <typename T>
bool numeric_board <T> :: is_win() {
    // Horizontally
    for (int i = 0; i < 3 ; ++i) {
        if(this->board[i][0] + this->board[i][1] + this->board[i][2] == 15
        && this->board[i][0] != 0 && this->board[i][1] !=0 && this->board[i][2] != 0)
            return true;
    }
    // Vertically
    for (int i = 0; i < 3 ; ++i) {
        if(this->board[0][i] + this->board[1][i] + this->board[2][i] == 15
        && this->board[0][i] != 0 && this->board[1][i] !=0 && this->board[2][i] != 0)
            return true;
    }
    // Diagonally
    if(this->board[0][0] + this->board[1][1] + this->board[2][2] == 15
    && this->board[0][0] != 0 && this->board[1][1] !=0 && this->board[2][2] != 0)
        return true;
    if(this->board[0][2] + this->board[1][1] + this->board[2][0] == 15
    && this->board[0][2] != 0 && this->board[1][1] !=0 && this->board[2][2] != 0)
        return true;

    return false;
}
template <typename T>
bool numeric_board <T> :: is_draw()
{
    if(this->n_moves == 9)
        return true;
    return false;
}

template <typename T>
bool numeric_board <T> :: game_is_over()
{
    if(is_win() || is_draw())
        return true;
    return false;
}


//--------------------------------------Random Player
template <typename T>
numeric_Random_Player <T>::numeric_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player ";
    this->name += this->symbol;


    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void numeric_Random_Player<T>::getmove(int& x, int& y) {
    while(true)
    {
        x = rand() % this->dimension;       // random(0,2)
        y = rand() % this->dimension;       // random(0,2)
        int pos;
        if(this->symbol % 2 != 0)             // if the random player plays with the odd numbers
        {
            pos = rand() % numeric_player<T>::odd.size();                // take a random valid odd number
            this->symbol = numeric_player<T>::odd[pos];
            numeric_player<T>::odd.erase(numeric_player<T>::odd.begin()+pos);
            break;
        }
        if(this->symbol % 2 == 0)            // if the random player plays with the even numbers
        {
            pos = rand() % numeric_player<T>::even.size();
            this->symbol = numeric_player<T>::even[pos];                // take a random valid even number
            numeric_player<T>::even.erase(numeric_player<T>::even.begin()+pos);  // erase the taken number
            break;
        }
    }

}
#endif //GAMES_OOP_G5_H
