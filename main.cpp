#include "bits/stdc++.h"
#include "G1.h"
#include "G2.h"
#include "G3.h"
#include "G4.h"
#include "G5.h"
#include "G6.h"
#include "G7.h"
#include "G8.h"
#include "G9.h"

using namespace std;

// choice for every game to create their player
void pyramid_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2);  // 1
void C4_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2);       // 2
void Tic_5x5(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2);         // 3
void words_choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2);    // 4
void numeric_Choice(string &p1name,string &p2name,Player <int> *(&players)[2],string &ch1,string &ch2);   // 5
void Misere_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2);   // 6
void X_O_4x4_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2);  // 7
void ultimate_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2); // 8
void Sus_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2); // 9

void mainMenu() {
    cout << string(30,'*')  << "  Main Menu  " << string(30,'*') << endl;
    cout << "Choose the game you want:\n";
    cout << "1. Pyramid X_O" << endl;
    cout << "2. Connect 4" << endl;
    cout << "3. 5x5 X_O" << endl;
    cout << "4. Words_X_O" << endl;
    cout << "5. Numeric X_O" << endl;
    cout << "6. Misere X_O" << endl;
    cout << "7. 4x4 X_O" << endl;
    cout << "8. Ultimate X_O" << endl;
    cout << "9. SUS Game" << endl;
    cout << "10. Exit\n";
}
void user_Inputs(string &p1name,string &p2name,string &ch1,string &ch2,string choice);
int main() {

    while (true) {

        mainMenu();
        string choice;
        cin >> choice;
        if (choice == "10") {
            cout << "Exiting the program.....\n";
            return 0;
        }

        Player<char> *players_Ch[2];
        Player<int> *players_Int[2];
        string p1name, p2name,ch1,ch2;

        user_Inputs(p1name,p2name,ch1,ch2,choice);

        if (choice == "1") {
            pyramid_Board <char> *board = new pyramid_Board<char>;
            pyramid_Choice(p1name,p2name,players_Ch,ch1,ch2);
            GameManager <char> gameManager(board,players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }

        }
        else if (choice == "2") {
            C4_board<char> *board = new C4_board<char>;
            C4_Choice(p1name, p2name, players_Ch,ch1,ch2);
            GameManager<char> gameManager(board, players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }
        }
        else if (choice == "3") {
            TicTacToe5x5Board<char> *board = new TicTacToe5x5Board<char>;
            Tic_5x5(p1name, p2name, players_Ch,ch1,ch2);
            GameManager<char> gameManager(board, players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }


        }
        else if (choice == "4") {
            words_board<char> *board = new words_board<char>;
            words_choice(p1name, p2name, players_Ch, ch1, ch2);
            GameManager<char> gameManager(board, players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }
        }
        else if (choice == "5") {
            numeric_board<int> *board = new numeric_board<int>;
            numeric_Choice(p1name, p2name, players_Int,ch1,ch2);
            GameManager<int> gameManager(board, players_Int);
            gameManager.run();
            delete board;
            for (auto &player: players_Int) {
                delete player;
            }


        }
        else if (choice == "6") {
            misere_board<char> *board = new misere_board<char>;
            Misere_Choice(p1name, p2name, players_Ch,ch1,ch2);
            GameManager<char> gameManager(board, players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }

        }
        else if (choice == "7") {
            X_O_4x4_Board<char> *board = new X_O_4x4_Board<char>;
            X_O_4x4_Choice(p1name, p2name, players_Ch,ch1,ch2);
            GameManager<char> gameManager(board, players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }


        }
        else if (choice == "8") {
            ultimate_board<char> *board = new ultimate_board<char>;
            ultimate_Choice(p1name,p2name,players_Ch,ch1,ch2);
            GameManager<char> gameManager(board,players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }

        }
        else if (choice == "9") {
            Sus_board<char> *board = new Sus_board<char>;
            Sus_Choice(p1name,p2name,players_Ch,ch1,ch2);
            GameManager<char> gameManager(board,players_Ch);
            gameManager.run();
            delete board;
            for (auto &player: players_Ch) {
                delete player;
            }
        }
        else {
            cout << "Invalid choice......\n";
        }
    }
}
//------------------------------------------------------------------------ Implementations
void user_Inputs(string &p1name,string &p2name,string &ch1,string &ch2,string choice)
{
    while(true)
    {
        cout << "Please enter the name of first player:";
        cin >> p1name;
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> ch1;

        if(ch1 != "1" && ch1 != "2")
        {
            cout << "Invalid choice...\n";
            continue;
        }
        cout << "Please enter the name of second player:";
        cin >> p2name;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> ch2;
        if(ch2 != "1" && ch2 != "2")
        {
            cout << "Invalid choice...\n";
            continue;
        }
        break;
    }
    if(choice != "9" && choice != "5" && choice != "4")
        cout << "Player 1 plays with (X) and Player 2 plays with (O).\n";
}
void pyramid_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new pyramid_Player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new pyramid_Random_Player<char>('X');


    if(ch2 == "1")
        players[1] = new pyramid_Player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new pyramid_Random_Player<char>('O');

}
void numeric_Choice(string &p1name,string &p2name,Player <int> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new numeric_player <int>(p1name, 1);
    else if(ch1 == "2")
        players[0] = new numeric_Random_Player <int>(3);

    if(ch2 == "1")
        players[1] = new numeric_player <int>(p2name, 2);

    else if(ch2 == "2")
        players[1] = new numeric_Random_Player <int>(4);
    cout << "Player 1 plays with odd numbers and Player 2 plays with even numbers.\n";


}
void C4_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new C4_player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new C4_Random_Player<char>('x');

    if(ch2 == "1")
        players[1] = new C4_player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new C4_Random_Player<char>('o');
}
void Misere_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new misere_Player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new misere_Random_Player<char>('X');

    if(ch2 == "1")
        players[1] = new misere_Player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new misere_Random_Player<char>('O');
}
void ultimate_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new ultimate_player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new ultimate_Random_Player<char>('x');

    if(ch2 == "1")
        players[1] = new ultimate_player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new ultimate_Random_Player<char>('o');
}
void Tic_5x5(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new TicTacToe5x5Player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new TicTacToe5x5Player_random<char>('X');

    if(ch2 == "1")
        players[1] = new TicTacToe5x5Player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new TicTacToe5x5Player_random<char>('O');
}
void X_O_4x4_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new X_O_4x4_Player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new X_O_4x4_Random_Player<char>('x');

    if(ch2 == "1")
        players[1] = new X_O_4x4_Player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new X_O_4x4_Random_Player<char>('o');
}
void words_choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2)
{

    if(ch1 == "1")
        players[0] = new words_Player<char>(p1name, 'X');
    else if(ch1 == "2")
        players[0] = new words_Random_Player<char>('X');

    if(ch2 == "1")
        players[1] = new words_Player<char>(p2name, 'O');

    else if(ch2 == "2")
        players[1] = new words_Random_Player<char>('O');
}
void Sus_Choice(string &p1name,string &p2name,Player <char> *(&players)[2],string &ch1,string &ch2) {
    if(ch1 == "1")
        players[0] = new Sus_Player<char>(p1name, 'S');
    else if(ch1 == "2")
        players[0] = new Sus_Random_Player<char>('S');

    if(ch2 == "1")
        players[1] = new Sus_Player<char>(p2name, 'U');

    else if(ch2 == "2")
        players[1] = new Sus_Random_Player<char>('U');
    cout << "Player 1 plays with (S) and Player 2 plays with (U).\n";

}
