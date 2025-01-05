#ifndef G8_H
#define G8_H
#include "bits/stdc++.h"
#include "BoardGame_Classes.h"
using namespace std;

//----------------------------------- Headers

//------------------------------------- ultimate Board
template <typename T>
class ultimate_board: public Board<T> {
public:
    static vector<char> subboards_wins;
    static vector<bool> updated_subboards;
    ultimate_board();
    bool update_board(int x, int y, T symbol);
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over() ;
    void update_subBoards();
    void generate_win_sub_boards();
};
//----------------------------------------- ultimate Player
template <typename T>
class ultimate_player : public Player<T> {
public:
    ultimate_player(string n, T symbol);
    ultimate_player(T symbol);
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
    void getmove(int &x, int &y) ;
};
//----------------------------------------- ultimate Random Player

template <typename T>
class ultimate_Random_Player : public RandomPlayer<T>{
public:
    ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//----------------------------------------- Implementation

//-------------------------------------------Static members

// vector that has the large board containing 9 places that reprsent each subboard winning.
template<typename T>
vector <char> ultimate_board<T>::subboards_wins(9,'0');

// vector that check if the subboard is won by player and updated with all symbol he has won to make the code faster
template<typename T>
vector <bool> ultimate_board<T>::updated_subboards(9,false);


//-------------------------------------------Player
template<typename T>
ultimate_player<T>::ultimate_player(string n, T symbol) :Player<T>( n, symbol) {}

template<typename T>
ultimate_player<T>::ultimate_player( T symbol) :Player<T>(symbol) {}

template<typename T>
T ultimate_player<T>::getsymbol() {
    return this->symbol;
}
template<typename T>
string ultimate_player<T>::getname() {
    return this->name;
}

template<typename T>
void ultimate_player<T>::getmove(int &x, int &y) {
    while (true) {
        cout << "Please enter the place you want to play, two numbers with space (e.g., 0 1):" << endl;
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
//------------------------------------------- Board

// this function to check the winning of every subboard in the main board.
template<typename T>
void ultimate_board<T>::generate_win_sub_boards() {
    //------------------------------ zero board
    // Horiz vert
    for (int i = 0; i < 3; ++i) {
        if(this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)
            this->subboards_wins[0] = this->board[i][0];
        if(this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)
            this->subboards_wins[0] = this->board[0][i];
    }
    // Diag
    if(this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)
        this->subboards_wins[0] = this->board[0][0];
    if(this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)
        this->subboards_wins[0] = this->board[0][2];

    //------------------------------ first board
    // Horiz
    for (int i = 0; i < 3; ++i) {
        if(this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][3] != 0)
            this->subboards_wins[1] = this->board[i][3];

    }
    // vert
    for (int j = 3; j < 6; ++j) {
        if(this->board[0][j] == this->board[1][j] && this->board[1][j] == this->board[2][j] && this->board[0][j] != 0)
            this->subboards_wins[1] = this->board[0][j];
    }
    // Diag
    if(this->board[0][3] == this->board[1][4] && this->board[1][4] == this->board[2][5] && this->board[0][3] != 0)
        this->subboards_wins[1] = this->board[0][3];
    if(this->board[0][5] == this->board[1][4] && this->board[1][4] == this->board[2][3] && this->board[0][5] != 0)
        this->subboards_wins[1] = this->board[0][5];

    //------------------------------ second board
    // Horiz
    for (int i = 0; i < 3; ++i) {
        if(this->board[i][6] == this->board[i][7] && this->board[i][7] == this->board[i][8] && this->board[i][6] != 0)
            this->subboards_wins[2] = this->board[i][6];

    }
    // vert
    for (int j = 6; j < 9; ++j) {
        if(this->board[0][j] == this->board[1][j] && this->board[1][j] == this->board[2][j] && this->board[0][j] != 0)
            this->subboards_wins[2] = this->board[0][j];
    }
    // Diag
    if(this->board[0][6] == this->board[1][7] && this->board[1][7] == this->board[2][8] && this->board[0][6] != 0)
        this->subboards_wins[2] = this->board[0][6];
    if(this->board[0][8] == this->board[1][7] && this->board[1][7] == this->board[2][6] && this->board[0][8] != 0)
        this->subboards_wins[2] = this->board[0][8];

    //------------------------------ Third board
    // Horiz
    for (int i = 3; i < 6; ++i) {
        if(this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)
            this->subboards_wins[3] = this->board[i][0];

    }
    // vert
    for (int j = 0; j < 3; ++j) {
        if(this->board[3][j] == this->board[4][j] && this->board[4][j] == this->board[5][j] && this->board[3][j] != 0)
            this->subboards_wins[3] = this->board[3][j];
    }
    // Diag
    if(this->board[3][0] == this->board[4][1] && this->board[4][1] == this->board[5][2] && this->board[3][0] != 0)
        this->subboards_wins[3] = this->board[3][0];
    if(this->board[3][2] == this->board[4][1] && this->board[4][1] == this->board[5][0] && this->board[5][0] != 0)
        this->subboards_wins[3] = this->board[3][2];

    //------------------------------ fourth board
    // Horiz and vert
    for (int i = 3; i < 6; ++i) {
        if(this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][4] != 0)
            this->subboards_wins[4] = this->board[i][3];
        if(this->board[3][i] == this->board[4][i] && this->board[4][i] == this->board[5][i] && this->board[3][i] != 0)
            this->subboards_wins[4] = this->board[3][i];

    }
    // Diag
    if(this->board[3][3] == this->board[4][4] && this->board[4][4] == this->board[5][5] && this->board[3][3] != 0)
        this->subboards_wins[4] = this->board[3][3];
    if(this->board[3][5] == this->board[4][4] && this->board[4][4] == this->board[5][3] && this->board[5][3] != 0)
        this->subboards_wins[4] = this->board[3][5];

    //------------------------------Fifth board
    // Horiz
    for (int i = 3; i < 6; ++i) {
        if(this->board[i][6] == this->board[i][7] && this->board[i][7] == this->board[i][8] && this->board[i][6] != 0)
            this->subboards_wins[5] = this->board[i][6];

    }
    // vert
    for (int j = 6; j < 9; ++j) {
        if(this->board[3][j] == this->board[4][j] && this->board[4][j] == this->board[5][j] && this->board[3][j] != 0)
            this->subboards_wins[5] = this->board[3][j];
    }
    // Diag
    if(this->board[3][6] == this->board[4][7] && this->board[4][7] == this->board[5][8] && this->board[3][6] != 0)
        this->subboards_wins[5] = this->board[3][6];
    if(this->board[3][8] == this->board[4][7] && this->board[4][7] == this->board[5][6] && this->board[5][6] != 0)
        this->subboards_wins[5] = this->board[3][8];

    //------------------------------ Sixth board
    // Horiz
    for (int i = 6; i < 9; ++i) {
        if(this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][1] != 0)
            this->subboards_wins[6] = this->board[i][1];
    }
    // vert
    for (int j = 0; j < 3; ++j) {
        if(this->board[6][j] == this->board[7][j] && this->board[7][j] == this->board[8][j] && this->board[7][j] != 0)
            this->subboards_wins[6] = this->board[7][j];
    }
    // Diag
    if(this->board[6][0] == this->board[7][1] && this->board[7][1] == this->board[8][2] && this->board[6][0] != 0)
        this->subboards_wins[6] = this->board[6][0];
    if(this->board[6][2] == this->board[7][1] && this->board[7][1] == this->board[8][0] && this->board[8][0] != 0)
        this->subboards_wins[6] = this->board[6][2];


    //------------------------------ Seventh board
    // Horiz
    for (int i = 6; i < 9; ++i) {
        if(this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][3] != 0)
            this->subboards_wins[7] = this->board[i][3];

    }
    // vert
    for (int j = 3; j < 6; ++j) {
        if(this->board[6][j] == this->board[7][j] && this->board[7][j] == this->board[8][j] && this->board[7][j] != 0)
            this->subboards_wins[7] = this->board[7][j];
    }
    // Diag
    if(this->board[6][3] == this->board[7][4] && this->board[7][4] == this->board[8][5] && this->board[6][3] != 0)
        this->subboards_wins[7] = this->board[6][3];
    if(this->board[6][5] == this->board[7][4] && this->board[7][4] == this->board[8][3] && this->board[8][3] != 0)
        this->subboards_wins[7] = this->board[6][5];

    //------------------------------ Eighth board
    // Horiz and vert
    for (int i = 6; i < 9; ++i) {
        if(this->board[i][6] == this->board[i][7] && this->board[i][7] == this->board[i][8] && this->board[i][8] != 0)
            this->subboards_wins[8] = this->board[i][6];
        if(this->board[6][i] == this->board[7][i] && this->board[7][i] == this->board[8][i] && this->board[6][i] != 0)
            this->subboards_wins[8] = this->board[6][i];

    }
    // Diag
    if(this->board[6][6] == this->board[7][7] && this->board[7][7] == this->board[8][8] && this->board[6][6] != 0)
        this->subboards_wins[8] = this->board[6][6];
    if(this->board[6][8] == this->board[7][7] && this->board[7][7] == this->board[8][6] && this->board[8][6] != 0)
        this->subboards_wins[8] = this->board[6][8];

}

// to update the subboards if some player has won with all its symbol
template<typename T>
void ultimate_board<T>::update_subBoards() {
    for (int i = 0; i < 9; ++i) {
        if(subboards_wins[i] != '0' && !updated_subboards[i]) {
            int x,i_temp;
            updated_subboards[i] = true;
           if(i < 3) {
               x = 0;
               i_temp = i;
           }
           else if(i < 6) {
               i_temp = i-3;
               x = 3;
           }
           else {
               i_temp = i-6;
               x = 6;
           }
           for (int j = x; j < x+3; ++j) {
                int y = i_temp *3;
                this->board[j][y] = subboards_wins[i];
                this->board[j][y+1] = subboards_wins[i];
                this->board[j][y+2] = subboards_wins[i];

           }
        }
    }
}

template<typename T>
ultimate_board<T>::ultimate_board() {
    this->rows = 9 ,this->columns = 9;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    // here reset all varibles to their intial states
    this->n_moves = 0;
    subboards_wins.assign(9, '0');
    updated_subboards.assign(9, false);
}
template<typename T>
void ultimate_board<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if(this->board[i][j] != 0)
                cout << " |  " << char(toupper(this->board[i][j])) << "  ";
            else
                cout << " | " << i << "," << j << " ";
            if((j+1) % 3 == 0 && j != 8)            // here to add the this shape after each 3 cells in the same row
                cout << "  |||  ";
        }
        cout << endl;
        // here to add a line and endl after each row
        if((i+1) % 3 == 0)
            cout <<  string(75,'_') << endl;
    }
    cout << endl;
}

template <typename T>
bool ultimate_board <T> :: update_board(int x, int y, T symbol) {
    bool is_random = false;
    if(symbol == 'x' || symbol == 'o')
        is_random = true;
    if(!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0))
    {
        this->board[x][y] = symbol;
        generate_win_sub_boards();      // check if the winning of all subboards
        update_subBoards();             // to update the subboard with the same symbol if a player wins in it
        return true;
    }
    if(!is_random)
        cout << "Invalid Choice...\n";
    return false;
}
// to check if three subboards wins in horizontally, vertically, diagonally
template <typename T>
bool ultimate_board <T> :: is_win() {
    /*
     0  1  2
     3  4  5
     6  7  8
     */
    // Horizontally
    for (int i = 0; i < 9; i += 3) {
        if(subboards_wins[i] == subboards_wins[i+1] && subboards_wins[i+1] == subboards_wins[i+2] && subboards_wins[i] != '0')
            return true;
    }
    // Vertically
    for (int i = 0; i < 3; i ++) {
        if(subboards_wins[i] == subboards_wins[i+3] && subboards_wins[i+3] == subboards_wins[i+6] && subboards_wins[i] != '0')
            return true;
    }
    // Diagonally
    if(subboards_wins[0] == subboards_wins[4] && subboards_wins[4] == subboards_wins[8] && subboards_wins[0] != '0') {
        return true;
    }
    if(subboards_wins[2] == subboards_wins[4] && subboards_wins[4] == subboards_wins[6] && subboards_wins[2] != '0') {
        return true;
    }
    return false;
}

template <typename T>
bool ultimate_board <T> :: is_draw()
{
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if(this->board[i][j] == 0)
                return false;
        }
    }
    return true;
}

template <typename T>
bool ultimate_board <T> :: game_is_over()
{
    if(is_win() || is_draw()) {
        return true;
    }
    return false;
}
//------------------------------------------ Random Player
template <typename T>
ultimate_Random_Player<T>::ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player ";
    this->name += this->symbol;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //G8_H
