CC = g++
CFLAGS = -std=c++20 -O2 -pedantic -Wall -Werror
CFLAGS += -I./include

SOURCES = src/FastAtoi.cpp src/ConfigReader.cpp src/OptionAdapter.cpp src/Serial.cpp src/Board.cpp src/main.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

build/%.o: src/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) build data/*
