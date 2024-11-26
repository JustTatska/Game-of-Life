#include <stdio.h>
#include "game.h"
#include <time.h>
#include <stdlib.h>

// Initialize the game board with random patterns
void init_game(struct cell board[15][15])
{
    srand(time(NULL)); // Seed random number generator

    // Initialize all cells as dead
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            board[i][j].existing = 0;
            board[i][j].future = 0;
        }
    }

    // Place creatures randomly
    for (int i = 1; i < 14; i++) 
    {
        for (int j = 1; j < 14; j++)
        {
            if (rand() % 4 == 0) // ~25% chance to be alive
            {
                board[i][j].existing = 1;

                // Ensure at least one neighbor for survivability
                if (rand() % 2 == 0)
                {
                    int dx = rand() % 3 - 1; // Random offset for neighbor
                    int dy = rand() % 3 - 1;
                    board[i + dx][j + dy].existing = 1;
                }
            }
        }
    }
}

// Print the current board state
void print_board(struct cell board[15][15])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (board[i][j].existing == 1)
            {
                printf("\033[32mo\033[0m"); // Green for living cells
            }
            else
            {
                printf("\033[37m.\033[0m"); // White for dead cells
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Calculate the next generation of the game
void calculate_game(struct cell board[15][15])
{
    for (int i = 1; i < 14; i++) 
    {
        for (int j = 1; j < 14; j++)
        {
            int newNeigh = count_neighbours(i, j, board);

            if (board[i][j].existing == 1 && newNeigh < 2)
            {
                board[i][j].future = 0; // Die from underpopulation
            }
            else if (board[i][j].existing == 1 && newNeigh >= 4)
            {
                board[i][j].future = 0; // Die from overpopulation
            }
            else if (board[i][j].existing == 1 && (newNeigh == 2 || newNeigh == 3))
            {
                board[i][j].future = 1; // Stay alive
            }
            else if (board[i][j].existing == 0 && newNeigh == 3)
            {
                board[i][j].future = 1; // Become alive
            }
        }
    }
}

// Count the number of neighbors for a cell
int count_neighbours(int i, int j, struct cell board[15][15])
{
    return board[i][j - 1].existing +
           board[i][j + 1].existing +
           board[i - 1][j - 1].existing +
           board[i - 1][j].existing +
           board[i - 1][j + 1].existing +
           board[i + 1][j - 1].existing +
           board[i + 1][j].existing +
           board[i + 1][j + 1].existing;
}

// Update the board for the next generation
void future_board(struct cell board[15][15])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            board[i][j].existing = board[i][j].future;
        }
    }
}
