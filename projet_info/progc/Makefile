# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = main.c avl.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = mon_programme

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

