NAME=race02

CC=clang

CFLAGS=-std=c11 -Wall -Wextra -Werror -Wpedantic

SRC=src/*.c

INC=inc/*.h

SRCCUR=*.c

INCCUR=*.h

all: RACE02


RACE02:
	cp $(SRC) .
	cp $(INC) .
	$(CC) $(CFLAGS) $(SRCCUR)  -o $(NAME)
	rm $(SRCCUR) $(INCCUR)


reinstall: uninstall RACE02


uninstall:
	rm $(NAME)



