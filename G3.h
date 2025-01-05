#ifndef G3_H
#define G3_H
#include "bits/stdc++.h"
#include "BoardGame_Classes.h"
using namespace std;
template <typename T>
class X_O_5x5_Board:public Board<T> {
private:
    vector<vector<bool>> rows_counted,columns_counted,left_diag_counted,right_diag_counted;
    int x_wins,o_wins;
public:
    static bool skip_round;
    X_O_5x5_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void check_three_in_a_row(int x, int y) ;
    void reset_variables();

};

template <typename T>
class X_O_5x5_Player : public Player<T> {
public:
    X_O_5x5_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_5x5_Random_Player : public RandomPlayer<T>{
public:
    X_O_5x5_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//-------------------------------------------------------------Implementation

//---------------------------------------------------------------Static varibales
template<typename T>
bool X_O_5x5_Board<T>::skip_round = false;

//---------------------------------------------------------------Board
template <typename T>
X_O_5x5_Board <T>::X_O_5x5_Board() {
    this-> rows = 5;
    this->columns = 5;
    this->n_moves = 0;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->  board[i] = new char[this->columns];
        for (int j = 0; j <this-> columns; j++) {
            this->board[i][j] = 0; // Initialize the board with empty cells
        }
    }
    reset_variables();
    this->n_moves = 0;
}

template <typename T>
bool X_O_5x5_Board <T>::update_board(int x, int y, T symbol)  {
    if(skip_round) {
        this->n_moves++;
        return true;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y <this-> columns &&this-> board[x][y] == 0) {
        this-> board[x][y] = symbol;
        ++this->n_moves;
        return true;
    }
    return false;
}

template <typename T>
     void X_O_5x5_Board <T>::display_board()   {
        for (int i = 0; i <this-> rows; i++) {
            for (int j = 0; j <this-> columns; j++) {
                cout << setw(2);
                if(this->board[i][j] != 0)
                    cout << " |  "  << this-> board[i][j] << " ";
                else
                    cout << " | "  << i << "," << j;
            }
            cout << endl;
        }
        cout << endl;
    }

template<typename T>
void X_O_5x5_Board<T>::reset_variables() {
    x_wins = o_wins = 0,skip_round = false;
    rows_counted.assign(5,vector<bool>(5,false));
    columns_counted.assign(5,vector<bool>(5,false));
    right_diag_counted.assign(5,vector<bool>(5,false));
    left_diag_counted.assign(5,vector<bool>(5,false));
}

template <typename T>
bool X_O_5x5_Board <T>::is_win()  {
    // Check all rows, columns, and diagonals for 3-in-a-row
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <this-> columns; j++) {
            if(this->board[i][j] == 0)
                continue;
            this->check_three_in_a_row(i, j);
        }
    }

    if(this->n_moves == 24) {
        if(o_wins > x_wins) {
            cout << "Player (X) took " << x_wins << " points.\n";
            cout << "Player (O) took " << o_wins << " points.\n";
            return true;
        }
        if(o_wins < x_wins) {
            skip_round = true;
        }
    }
    if(this->n_moves == 25) {
        cout << "Player (X) took " << x_wins << " points.\n";
        cout << "Player (O) took " << o_wins << " points.\n";
        return true;
    }
    return false;
}

template <typename T>
bool X_O_5x5_Board<T>::is_draw()  {
        return this->n_moves == 24 && x_wins == o_wins && !is_win();
    }

template <typename T>
bool X_O_5x5_Board<T>::game_is_over()  {
        return this->is_win() || this-> is_draw();
}
template <typename T>
void X_O_5x5_Board<T>::check_three_in_a_row(int x, int y) {
    char symbol = this->board[x][y];
    // Check horizontal
    if (y + 2 < this->columns &&
        this->board[x][y + 1] == symbol && !rows_counted[x][y] &&
        this->board[x][y + 2] == symbol) {
        symbol == 'X'? x_wins++:o_wins++;
        rows_counted[x][y] = true;
        }

    // Check vertical
    if (x + 2 < this->rows &&
        this->board[x + 1][y] == symbol &&!columns_counted[x][y]&&
        this->board[x + 2][y] == symbol) {
        symbol == 'X'? x_wins++:o_wins++;
        columns_counted[x][y] = true;

        }

    // Check diagonal (top-left to bottom-right)
    if (x + 2 < this->rows && y + 2 < this->columns && !left_diag_counted[x][y]&&
        this->board[x + 1][y + 1] == symbol &&
        this->board[x + 2][y + 2] == symbol)
        {
        symbol == 'X'? x_wins++:o_wins++;
        left_diag_counted[x][y] = true;
        }

    // Check diagonal (top-right to bottom-left)
    if (x + 2 < this->rows && y - 2 >= 0 &&!right_diag_counted[x][y]&&
        this->board[x + 1][y - 1] == symbol &&
        this->board[x + 2][y - 2] == symbol) {
        symbol == 'X'? x_wins++:o_wins++;
        right_diag_counted[x][y] = true;
        }
}
// Player implementation
template <typename T>

X_O_5x5_Player<T>::X_O_5x5_Player(std::string name, T symbol) : Player<T>( name, symbol) {}
template <typename T>
void X_O_5x5_Player<T>:: getmove(int& x, int& y)  {
    if(X_O_5x5_Board<T>::skip_round) return;

    cout << this->name << "'s turn (" << this->symbol << "). Enter your move (row and column):";
    cin >> x >> y;


}
//------------------------------------------ Random Player
template <typename T>
X_O_5x5_Random_Player<T>::X_O_5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player ";
    this->name += this->symbol;

    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_5x5_Random_Player<T>::getmove(int& x, int& y) {
    if(X_O_5x5_Board<T>::skip_round) return;
    x = rand() % this->dimension; // 0 5
    y = rand() % this->dimension;

}

#endif // G3_H