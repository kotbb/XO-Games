
#ifndef G9_H
#define G9_H
#include "bits/stdc++.h"
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Sus_board:public Board<T> {
private:
    T current_symbol;
    int S_wins,U_wins;
    vector<bool> check_counted_before;             // to check if these places has been won before and prevent count again in the same places
public:
    static bool skip_round;                        // bool to skip a round if the player that plays with U wins and skip the winning of S player
    Sus_board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Sus_Player : public Player<T> {
public:
    Sus_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class Sus_Random_Player : public RandomPlayer<T>{
public:
    Sus_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

//--------------------------------------- Static varibles

template<typename T>
bool Sus_board<T>::skip_round = false;
//--------------------------------------- Board

// Constructor for Sus_Board
template <typename T>
Sus_board<T>::Sus_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    // reset the variables to their intial state
    this->n_moves = this->S_wins = this->U_wins = 0;
    check_counted_before.assign(8,false);
}

template <typename T>
bool Sus_board<T>::update_board(int x, int y, T symbol) {
    current_symbol = symbol;
    if(skip_round) {
        this->n_moves++;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && this->board[x][y] == 0) {

        this->n_moves++;
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Sus_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
    is_win();
    cout << "Player (S) took " << S_wins << " points" << string(27,' ') << "Player (U) took " << U_wins << " points\n";
    cout << endl;

}

// Returns true if there is any winner
template <typename T>
bool Sus_board<T>::is_win() {
    // Horizontally && Vertically
    for (int i = 0; i < 3; ++i) {
        if(this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S'
            && !check_counted_before[i])
        {
            check_counted_before[i] = true;
            current_symbol == 'S'? S_wins++ : U_wins++;
        }
        if(this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S'
            && !check_counted_before[i+3])
        {
            check_counted_before[i+3] = true;
            current_symbol == 'S'? S_wins++ : U_wins++;
        }
    }
    // Diagonally
    if(this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S'
        && !check_counted_before[6])
    {
        check_counted_before[6] = true;
        current_symbol == 'S'? S_wins++ : U_wins++;
    }
    if(this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S'
        && !check_counted_before[7])
    {
        check_counted_before[7] = true;
        current_symbol == 'S'? S_wins++ : U_wins++;
    }

    if(this->n_moves == 9) {
        if(U_wins > S_wins)
            skip_round = true;
        if(S_wins > U_wins) {
            return true;
        }
    }
    // this indicates that U is won because it skip a round and S doesn't win in the move 9 and it doesn't ends in draw
    if(this->n_moves == 10) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Sus_board<T>::is_draw() {
    return (this->n_moves == 9 && S_wins == U_wins && !is_win());
}

template <typename T>
bool Sus_board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Sus_Player
template <typename T>
Sus_Player<T>::Sus_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Sus_Player<T>::getmove(int& x, int& y) {
    if(Sus_board<T>::skip_round) return;                         // to prevent the player from playing if it is in the state of the skipping the round
    while(true){
        cout << "Please enter the place you want to play the " << this->symbol << ". Enter x and y (0 to 2) separated by spaces:" << endl;
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

// Constructor for Sus_Random_Player
template <typename T>
Sus_Random_Player<T>::Sus_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player ";
    this->name += this->symbol;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Sus_Random_Player<T>::getmove(int& x, int& y) {
    if(Sus_board<T>::skip_round) return;                       // to prevent the random player from playing if it is in the state of the skipping the round
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif //G9_H
