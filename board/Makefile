ARDUINO_CLI = arduino-cli
BOARD = arduino:avr:uno
PORT ?= /dev/ttyACM0

all: compile upload

compile:
	$(ARDUINO_CLI) compile -b $(BOARD) board.ino

upload:
	$(ARDUINO_CLI) upload -p $(PORT) -b $(BOARD) board.ino

.PHONY: all compile upload
