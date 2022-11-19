COMPILER=g++
BUILD=build
OUTPUT=out

# Build the output program.
$(OUTPUT)/output: $(BUILD)/*.o
	$(COMPILER) $(BUILD)/*.o -o $@

# Bulid serial library.
$(BUILD)/serial_port.o: lib/src/serial_port.cpp lib/include/cpp_serial.hpp lib/include/exception.hpp
	$(COMPILER) -c $< -o $@

# Build board header.
$(BUILD)/board.o: src/board.cpp include/board.hpp
	$(COMPILER) -c $< -o $@

# Build config_reader header.
$(BUILD)/config_reader.o: src/config_reader.cpp include/config_reader.hpp
	$(COMPILER) -c $< -o $@

# Build main program.
$(BUILD)/main.o: src/main.cpp
	$(COMPILER) -c $< -o $@

build:
	mkdir $(BUILD)

out:
	mkdir $(OUTPUT)

clean:
	rm -rf $(BUILD) output

.PHONY: build clean
