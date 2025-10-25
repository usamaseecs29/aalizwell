#ifndef AALIZWELL_CONSOLE_H
#define AALIZWELL_CONSOLE_H

#include <string>
#include <cwchar>

#include <windows.h>

// Console drawing helpers (Win32).

void gotoxy(int x, int y);
void setColor(int attr);
void hidecursor();
void printUnicode(int x, int y, const std::wstring& text, int color);

// Sprite helpers
void clearSprite(int x, int y, int lines = 3);
void drawPlayer(int px, int py, const std::string& p1, const std::string& p2, const std::string& p3, int color = 10);
void drawEnemyStrings(int ex, int ey, const std::string& e1, const std::string& e2, const std::string& e3, int color = 12);

#endif