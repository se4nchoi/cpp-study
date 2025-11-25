# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g # -g adds debug symbols

# --- Project Structure ---

# 1. Define the output directory for our compiled files.
BUILD_DIR = build

# 2. Find all .cpp source files recursively in the current directory.
#    The result will be a list like: 2025-11-23/blinky_bare_metal.cpp 2025-11-26/modern_saftey.cpp
SRCS = $(shell find . -name "*.cpp")

# Tell make where to find source files.
# This creates a unique, sorted list of directories containing our .cpp files.
VPATH = $(sort $(dir $(SRCS)))

# 3. Generate the names of the target executables.
#    This takes the list from SRCS, strips the path and the .cpp extension,
#    and prepends the build directory.
#    e.g., 2025-11-26/modern_saftey.cpp -> build/modern_saftey
TARGETS = $(patsubst %.cpp,$(BUILD_DIR)/%,$(notdir $(SRCS)))

# --- Build Rules ---

# The 'all' target is the default. It depends on all our executables.
# Typing 'make' will build everything in the TARGETS list.
.PHONY: all
all: $(TARGETS)

# This is a generic "pattern rule". It tells make how to build ANY target
# in the BUILD_DIR from a .cpp file with the same name.
$(BUILD_DIR)/%: %.cpp
	@echo "Compiling $< -> $@"
	@mkdir -p $(BUILD_DIR) # Create build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule to clean up all compiled files.
.PHONY: clean
clean:
	@echo "Cleaning up build artifacts..."
	rm -rf $(BUILD_DIR)