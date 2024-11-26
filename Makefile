# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c game.c utils.c

# Object file
OBJ = $(SRC:.c=.o)

# Target to build the final executable
GoL: $(OBJ)
	$(CC) $(CFLAGS) -o GoL $(OBJ)

# Compiling rules for the .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up object files and executable
clean:
	rm -f *.o GoL
