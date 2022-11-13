COMPILER=g++
BUILD=build

$(BUILD)/output: $(BUILD)/serial_port.o $(BUILD)/main.o
	$(COMPILER) $(BUILD)/*.o -o $@

$(BUILD)/serial_port.o: lib/src/serial_port.cpp lib/include/cpp_serial.hpp lib/include/exception.hpp
	$(COMPILER) -c $< -o $@

$(BUILD)/main.o: src/main.cpp
	$(COMPILER) -c $< -o $@

build:
	mkdir $(BUILD)

clean:
	rm -rf $(BUILD) output

.PHONY: build clean
