CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread
LDFLAGS = -largtable2 -pthread
SRC = src
OBJ = $(SRC)/genmath.o $(SRC)/test.o $(SRC)/benchmark.o $(SRC)/helpers.o $(SRC)/cli.o $(SRC)/parallel.o
TARGET = linxel
PREFIX ?= $(HOME)/bin

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)
 
$(SRC)/test.o: $(SRC)/test.c $(SRC)/genmath.h $(SRC)/globals.h
	$(CC) $(CFLAGS) -c $(SRC)/test.c -o $(SRC)/test.o

$(SRC)/genmath.o: $(SRC)/genmath.c $(SRC)/genmath.h $(SRC)/globals.h
	$(CC) $(CFLAGS) -c $(SRC)/genmath.c -o $(SRC)/genmath.o

$(SRC)/benchmark.o: $(SRC)/benchmark.c $(SRC)/benchmark.h $(SRC)/globals.h
	$(CC) $(CFLAGS) -c $(SRC)/benchmark.c -o $(SRC)/benchmark.o

$(SRC)/helpers.o: $(SRC)/helpers.c $(SRC)/helpers.h $(SRC)/globals.h
	$(CC) $(CFLAGS) -c $(SRC)/helpers.c -o $(SRC)/helpers.o

$(SRC)/cli.o: $(SRC)/cli.c $(SRC)/cli.h $(SRC)/globals.h
	$(CC) $(CFLAGS) -c $(SRC)/cli.c -o $(SRC)/cli.o

$(SRC)/parallel.o: $(SRC)/parallel.cpp $(SRC)/genmath.h $(SRC)/globals.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

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