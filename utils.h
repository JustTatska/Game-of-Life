#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
// Declare Windows-specific functions
void enable_ansi_escape_codes();
void adjust_window_size();
#endif

// Declare common utility functions
void clear_screen();

#endif
