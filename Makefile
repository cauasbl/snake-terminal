CC = gcc
SRC = src
INCLUDE = include
OUT = output
BIN = projeto-snake.exe

all:
	$(CC) $(SRC)/*.c -I$(INCLUDE) -o $(OUT)/$(BIN)

clean:
	del $(OUT)\$(BIN)
