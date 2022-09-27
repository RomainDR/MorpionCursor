#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

const short gridSize = 3;
int grid[gridSize][gridSize] = { {0,0,0}, {0,0,0}, {0,0,0} };
short cursorX = 0, cursorY = 0;
char player1 = 'X', player2 = '0';
string name1, name2;
bool player1Turn = true;
bool moveCursor = true;

bool CheckWin(short _player)
{
    int _win = 0;
    for (short h = 0; h < 3; h++) {
        for (short v = 0; v < 3; v++)
        {
            _win += (grid[h][v] == _player);
        }
        if (_win == 3) return true;
        _win = 0;
    }
    for (short v = 0; v < 3; v++) {
        for (short h = 0; h < 3; h++)
        {
            _win += grid[h][v] == _player;
        }
        if (_win == 3) return true;
        _win = 0;
    }
    for (short v = 0, h = 0; v < 3; v++, h++) {
        _win += grid[h][v] == _player;
    }
    if (_win == 3) return true;
    _win = 0;
    for (short h = 0, v = 2; h < 3; h++, v--) {
        _win += grid[h][v] == _player;
    }
    if (_win == 3) return true;
    _win = 0;
    return false;
}

void SetColorPlayer()
{
    const HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(_hConsole, player1Turn ? 3 : 2);
}

bool IsValidCase(short _horizontal, short _vertical)
{
    return grid[_horizontal][_vertical] == 0;
}
char CheckSymbol(int _horizontal, int _vertical)
{
    return grid[_horizontal][_vertical] == 0 ? ' ' : (grid[_horizontal][_vertical] == 1 ? player1 : player2);
}
void ShowInterface()
{
    cout << "====================" << endl;
    cout << "Tour du joueur " << (player1Turn ? name1 : name2) << endl;
    string grid = "";
    for (short h = 0; h < gridSize; h++) {
        for (short v = 0; v < gridSize; v++) {
            grid = grid + " [" + (cursorX == v && cursorY == h && IsValidCase(cursorY, cursorX) ? '_' : CheckSymbol(h, v)) + "] ";
        }
        grid += "\n";
    }
    cout << grid << endl;
    cout << "====================" << endl;
}
void MoveCursor()
{    
    if (moveCursor) {
        char _mover;
        cout << "How you would move the cursor ? [Z,Q,S,D] (or type '0', if you don't move): ";
        cin >> _mover;
        if (_mover == 'Z' || _mover == 'z') {
            if (cursorY == 0) {
                cout << "The cursor is already on top. Retry" << endl;
                MoveCursor();
                return;
            }
            if (IsValidCase(cursorY - 1, cursorX) && cursorY - 1 >= 0)
                cursorY--;
            else if (IsValidCase(cursorY - 2, cursorX) && cursorY - 2 >= 0)
                cursorY -= 2;
            else {
                cout << "The cursor is already on top. Retry" << endl;
                MoveCursor();
                return;
            }
        }if (_mover == 'q' || _mover == 'Q') {
            if (cursorX == 0) {
                cout << "The cursor is already on right. Retry" << endl;
                MoveCursor();
                return;
            }
            if (IsValidCase(cursorY, cursorX - 1) && cursorX - 1 >= 0)
                cursorX--;
            else if (IsValidCase(cursorY, cursorX - 2) && cursorX - 2 >= 0)
                cursorX -= 2;
            else {
                cout << "The cursor is already on right. Retry" << endl;
                MoveCursor();
                return;
            }
        }if (_mover == 'S' || _mover == 's') {
            if (cursorY == 2) {
                cout << "The cursor is already on bottom. Retry" << endl;
                MoveCursor();
                return;
            }
            if (IsValidCase(cursorY + 1, cursorX) && cursorY + 1 <= 2)
                cursorY++;
            else if (IsValidCase(cursorY + 2, cursorX) && cursorY + 2 <= 2)
                cursorY += 2;
            else {
                cout << "The cursor is already on bottom. Retry" << endl;
                MoveCursor();
                return;
            }
        }if (_mover == 'D' || _mover == 'd') {
            if (cursorX == 2) {
                cout << "The cursor is already on right. Retry" << endl;
                MoveCursor();
                return;
            }
            if (IsValidCase(cursorY, cursorX + 1) && cursorX + 1 <= 2)
                cursorX++;
            else if (IsValidCase(cursorY, cursorX + 2) && cursorX + 2 <= 2)
                cursorY += 2;
            else {
                cout << "The cursor is already on top. Retry" << endl;
                MoveCursor();
                return;
            }
        }
        else if (_mover == '0')
            moveCursor = !moveCursor;

        system("CLS");
        ShowInterface();
        MoveCursor();
    }
    else {
        moveCursor = !moveCursor;
        system("CLS");
        ShowInterface();
    }
}
void SetPlayerName()
{
    cout << "Select the name of player 1: ";
    cin >> name1;
    cout << "Select the name of player 2: ";
    cin >> name2;
}
void Game()
{
    SetColorPlayer();
    ShowInterface();
    MoveCursor();
    char _continue;
    cout << "Valid cursor ? [Y/N]: ";
    cin >> _continue;
    if (_continue == 'N' || _continue == 'n') {
        system("CLS");
        Game();
    }
    else if(_continue == 'Y' || _continue == 'y'){
        if (!IsValidCase(cursorY, cursorX))
        {
            system("CLS");
            cout << "Case not available. Retry." << endl;
            Game();
        }
        grid[cursorY][cursorX] = player1Turn ? 1 : 2;
        cursorX = 0;
        cursorY = 0;
        if (CheckWin(player1Turn ? 1 : 2)) {
            cout << "Le joueur " << (player1Turn ? 1 : 2) << " viens de gagner" << endl;
            ShowInterface();
            return;
        }
        player1Turn = !player1Turn;
        system("CLS");
        Game();
    }
    else {
        cout << "input not detected. Retry" << endl;
        Game();
    }
}

int main()
{
    const HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(_hConsole, 7);
    SetPlayerName();
    system("CLS");
    Game();
}