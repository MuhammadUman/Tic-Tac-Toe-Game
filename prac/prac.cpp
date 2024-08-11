#include <iostream>
#include <string>
#include<cstdlib>
#include<ctime>
using namespace std;

class Game {
private:
    static const int size = 3;
    string arr[size][size];
public:
    Game() {
        // Initializing Values For The Tic Tac Toe Graph
        cout << "Enter The Number You Want To Add The Mark At" << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                arr[i][j] = to_string(i * size + j + 1);   
            }
        }
    }

    void Graph() {
        // Displaying The Graph
        cout << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << arr[i][j];
                if (j < size - 1) {
                    cout << " | ";
                }
            }
            cout << endl;
            if (i < size - 1) {
                cout << "--+---+--" << endl;
            }
        }
    }
  
    void AddToGraph(int choice, const string& mark) {
        int a = 0;
        do {
            int row = (choice - 1) / size;
            int col = (choice - 1) % size;
            if (arr[row][col] != "X" && arr[row][col] != "O") {
                arr[row][col] = mark;
                a = 1;
            }
            else {
                cout << "Cell already taken. Choose another cell." << endl;
                cin >> choice;
            }
        } while (a == 0);
    }
    bool checkWinX() {
        int checkrow[size] = { 0 };
        int checkcol[size] = { 0 };
        int rightdiag = 0;
        int leftdiag = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][j] == "X") {
                    checkrow[i]++;
                    if (checkrow[i] == 3) {
                        Graph();
                        cout << "\n\nCongratulations Player 1 Has Won";
                        exit(0);
                    }
                }
                if (arr[j][i] == "X") {
                    checkcol[i]++;
                    if (checkcol[i] == 3) {
                        Graph();
                        cout << "\n\nCongratulations Player 1 Has Won";
                        exit(0);
                    }
                }
                if (i == j) {
                    if (arr[i][j] == "X")
                    {
                        rightdiag++;
                        if (rightdiag == 3)
                        {
                            Graph();
                            cout << "\n\nCongratulations Player 1 Has Won";
                            exit(0);
                        }
                    }
                    if (arr[j][2 - j] == "X")
                    {
                        leftdiag++;
                        if (leftdiag == 3)
                        {
                            Graph();
                            cout << "\n\nCongratulations Player 1 Has Won";
                            exit(0);
                        }
                    }
                }

            }
        }
        return false;
    }
    bool checkWinO() {
        int checkrow[size] = { 0 };
        int checkcol[size] = { 0 };
        int rightdiag = 0;
        int leftdiag = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][j] == "O") {
                    checkrow[i]++;
                    if (checkrow[i] == 3) {
                        Graph();
                        cout << "\n\nCongratulations Player 2 Has Won";
                        exit(0);
                    }
                }
                if (arr[j][i] == "O") {
                    checkcol[i]++;
                    if (checkcol[i] == 3) {
                        Graph();
                        cout << "\n\nCongratulations Player 2 Has Won";
                        exit(0);
                    }
                }
                if (i == j) {
                    if (arr[i][j] == "O")
                    {
                        rightdiag++;
                        if (rightdiag == 3)
                        {
                            Graph();
                            cout << "\n\nCongratulations Player 2 Has Won";
                            exit(0);
                        }
                    }
                    if (arr[j][2 - j] == "O")
                    {
                        leftdiag++;
                        if (leftdiag == 3)
                        {
                            Graph();
                            cout << "\n\nCongratulations Player 2 Has Won";
                            exit(0);
                        }
                    }
                }

            }
        }
        return false;
    }
    void checkDraw() {
        int chk = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][j] == "O" || arr[i][j] == "X")
                {
                    chk += 1;
                }
            }
        }
        if (chk == 9) {
            cout << "\n\nGame Over! It Was A Draw!";
            exit(0);
        }
    }
    bool checkfill(int choice) {
        int row = (choice - 1) / size;
        int col= (choice - 1) % size;
        if (arr[row][col] != "X" && arr[row][col] != "O") {
            return true;
        }
        else false;
    }

};

class Player {
protected:
    string mark;
    Game* game;
public:
    Player(){}
    Player(Game* g, const string& m) : game(g), mark(m) {}

   virtual void addOption() {
        int choice;
        cout << "Player '" << mark << "' Turn: ";
        cin >> choice;
        if (choice >= 1 && choice <= 9) {
            game->AddToGraph(choice, mark);
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
        }
    }
};
class AI : public Player {

public:
    AI(Game*g, const string& m): Player(g,m){}
    void addOption() override {
        int choice;
        cout << "AI '" << mark << "' Turn" << endl;
        do {
            srand(static_cast<unsigned int>(time(nullptr)));
            for (int i = 0; i < 10; ++i) {
                choice = rand() % 9 + 1;
            }
        } while (game->checkfill(choice) == false);
        game->AddToGraph(choice,mark);
    }
};

int main() {
    cout << "Press 1 For Ai And 2 For Double Player" << endl;
    int option;
    cin >> option;
    Game game;
    Player player1(&game, "X");
    Player player2(&game, "O");
    AI ai(&game, "O");
    if (option == 2) {
        for (int i = 0; i < 9; i++) {
            game.Graph();
            if (i % 2 == 0) {
                player1.addOption();
            }
            else {
                player2.addOption();
            }
            game.checkWinX();
            game.checkWinO();
            game.checkDraw();
        }
    }
    if (option == 1) {
        for (int i = 0; i < 9; i++) {
            game.Graph();
            if (i % 2 == 0) {
                player1.addOption();
            }
            else {
                ai.addOption();
            }
            game.checkWinX();
            game.checkWinO();
            game.checkDraw();
            cout<<"bye"<<endl;
        }
    }

    return 0;
}
