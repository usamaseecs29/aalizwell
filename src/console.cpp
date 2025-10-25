// src/console.cpp
// Project: Aal Iz Well - Tale of Seecs

#include "console.h"

#include <windows.h>
#include <io.h>     // For _setmode
#include <fcntl.h>  // For Unicodes

#include <iostream>
#include <string>
using namespace std;

static HANDLE g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) {
    COORD c; c.X = (SHORT)x; c.Y = (SHORT)y;
    SetConsoleCursorPosition(g_hConsole, c);
}

void setColor(int attr) {
    SetConsoleTextAttribute(g_hConsole, attr);
}

void hidecursor() {
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(g_hConsole, &info);
}

void printUnicode(int x, int y, const wstring& text, int color) {
    gotoxy(x, y);
    setColor(color);
    _setmode(_fileno(stdout), _O_U16TEXT);
    wcout << text;
    _setmode(_fileno(stdout), _O_TEXT);
    setColor(7);
}

void clearSprite(int x, int y, int lines) {
    for (int i = 0; i < lines; ++i) {
        gotoxy(x, y + i);
        cout << "        ";
    }
}

void drawPlayer(int px, int py, const string& p1, const string& p2, const string& p3, int color) {
    setColor(color);
    gotoxy(px, py);     cout << p1;
    gotoxy(px, py + 1); cout << p2;
    gotoxy(px, py + 2); cout << p3;
    setColor(7);
}

void drawEnemyStrings(int ex, int ey, const string& e1, const string& e2, const string& e3, int color) {
    setColor(color);
    gotoxy(ex, ey);     cout << e1;
    gotoxy(ex, ey + 1); cout << e2;
    gotoxy(ex, ey + 2); cout << e3;
    setColor(7);
    }