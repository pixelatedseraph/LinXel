CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src
OBJ = $(SRC)/genmath.o $(SRC)/test.o $(SRC)/benchmark.o $(SRC)/helpers.o
TARGET = linxel
PREFIX ?= $(HOME)/bin

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(SRC)/test.o: $(SRC)/test.c $(SRC)/genmath.h
	$(CC) $(CFLAGS) -c $(SRC)/test.c -o $(SRC)/test.o

$(SRC)/genmath.o: $(SRC)/genmath.c $(SRC)/genmath.h
	$(CC) $(CFLAGS) -c $(SRC)/genmath.c -o $(SRC)/genmath.o

$(SRC)/benchmark.o: $(SRC)/benchmark.c $(SRC)/benchmark.h
	$(CC) $(CFLAGS) -c $(SRC)/benchmark.c -o $(SRC)/benchmark.o

$(SRC)/helpers.o: $(SRC)/helpers.c $(SRC)/helpers.h
	$(CC) $(CFLAGS) -c $(SRC)/helpers.c -o $(SRC)/helpers.o

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	@mkdir -p $(PREFIX)
	cp $(TARGET) $(PREFIX)
	chmod +x $(PREFIX)/$(TARGET)
	@echo "Installed $(TARGET) to $(PREFIX) (add $(PREFIX) to PATH if needed)"

nuke: 
	rm -f $(OBJ) $(TARGET)

.PHONY: nuke install run