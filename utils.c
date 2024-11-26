#include <windows.h>
#include "utils.h"

// enabling virtual terminal processing manually as it wont work otherwise
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// Function to enable ANSI escape codes on Windows
void enable_ansi_escape_codes() {
    DWORD mode;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    // Check if the console supports ANSI escape sequences
    if (GetConsoleMode(hStdOut, &mode)) {
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;  
        SetConsoleMode(hStdOut, mode);  
    }
}

// Function to adjust the window size (example sets 80x25)
void adjust_window_size() {
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = 80;  // Width (columns)
        rect.bottom = 25; // Height (rows)
        AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), FALSE);
        MoveWindow(hwnd, 0, 0, rect.right - rect.left, rect.bottom - rect.top, TRUE);
    }
}


void clear_screen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = {0, 0};

    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Get console size
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the console with spaces
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) return;

    // Reset the attributes
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    // Move the cursor to the top-left corner
    SetConsoleCursorPosition(hConsole, homeCoords);
}
