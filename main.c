#include <stdio.h>
#include "cell.h"     // For struct cell
#include "game.h"     // For init_game(), calculate_game(), future_board()
#include "utils.h"    // For clear_screen(), enable_ansi_escape_codes(), adjust_window_size()

#ifdef _WIN32
#include <windows.h>
#include <conio.h> // For kbhit() and getch()
#else
#include <unistd.h>
#endif

int main()
{
#ifdef _WIN32
    enable_ansi_escape_codes(); // Enable ANSI escape codes for Windows
#endif
    adjust_window_size();

    struct cell board[15][15] = {{{0, 0}}}; // Initialize board

    init_game(board); // Set up the initial board state

    // Main game loop (runs until user presses ESC)
    while (1)
    {
        clear_screen();        // Clear the screen
        print_board(board);    // Display the board
        calculate_game(board); // Calculate the next generation
        future_board(board);   // Update the board

#ifdef _WIN32
        // Sleep for 500 milliseconds (Windows)
        Sleep(500); 

        // Check if a key has been pressed
        if (kbhit()) {
            char ch = getch();
            if (ch == 27) {
                break; // Exit the loop if ESC is pressed
            }
        }
#else
        // Pause for 500 milliseconds (POSIX)
        usleep(500000);

        
#endif
    }

    return 0;
}
