COMPILER=g++
BUILD=build

# Build the output program.
$(BUILD)/output: $(BUILD)/serial_port.o $(BUILD)/get_opt.o $(BUILD)/main.o
	$(COMPILER) $(BUILD)/*.o -o $@

# Bulid serial library.
$(BUILD)/serial_port.o: lib/src/serial_port.cpp lib/include/cpp_serial.hpp lib/include/exception.hpp
	$(COMPILER) -c $< -o $@

# Build get_opt library.
$(BUILD)/get_opt.o: src/get_opt.cpp include/get_opt.hpp include/exception.hpp
	$(COMPILER) -c $< -o $@

# Build main program.
$(BUILD)/main.o: src/main.cpp
	$(COMPILER) -c $< -o $@

build:
	mkdir $(BUILD)

clean:
	rm -rf $(BUILD) output

.PHONY: build clean
