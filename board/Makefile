ARDUINO_CLI = arduino-cli

# For Arduino UNO.
# BOARD = arduino:avr:uno
# PORT ?= /dev/ttyACM0

# For ESP32 dev kit.
BOARD = esp32:esp32:esp32
PORT ?= /dev/ttyUSB0

all: compile upload

compile:
	$(ARDUINO_CLI) compile -b $(BOARD) board.ino

upload:
	$(ARDUINO_CLI) upload -p $(PORT) -b $(BOARD) board.ino

.PHONY: all compile upload
