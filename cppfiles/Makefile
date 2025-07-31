# Makefile for C++ project
# Cross-platform build system for the cppsample project
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
DEBUGFLAGS = -g -O0 -D_DEBUG
RELEASEFLAGS = -O2 -DNDEBUG

# Platform detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    PLATFORM_FLAGS = -D__APPLE__
else ifeq ($(UNAME_S),Linux)
    PLATFORM_FLAGS = -D__LINUX__
else
    PLATFORM_FLAGS = -D__WINDOWS__
endif

CXXFLAGS += $(PLATFORM_FLAGS)

# Directories
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Source files
MAIN_SRC = file.cpp
LIB_SRC = StaticLib1.cpp pch.cpp
HEADERS = pch.h framework.h

# Object files
MAIN_OBJ = $(OBJDIR)/file.o
LIB_OBJ = $(LIB_SRC:%.cpp=$(OBJDIR)/%.o)
ALL_OBJ = $(MAIN_OBJ) $(LIB_OBJ)

# Target executable
TARGET = $(BINDIR)/MainApp

# Default build type
BUILD_TYPE ?= debug

# Set flags based on build type
ifeq ($(BUILD_TYPE), release)
    CXXFLAGS += $(RELEASEFLAGS)
else
    CXXFLAGS += $(DEBUGFLAGS)
endif

# Default target
all: $(TARGET)

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Build the executable
$(TARGET): $(ALL_OBJ) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "Build artifacts cleaned"

# Build release version
release:
	$(MAKE) BUILD_TYPE=release

# Build debug version  
debug:
	$(MAKE) BUILD_TYPE=debug

# Run the program
run: $(TARGET)
	./$(TARGET)

# Test target (same as run for this project)
test: run

# Install target (copies to /usr/local/bin)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/MainApp
	@echo "Installation complete"

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the main executable (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  debug    - Build debug version (default)"
	@echo "  release  - Build optimized release version"
	@echo "  run      - Build and run the program"
	@echo "  test     - Build and test the program"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  help     - Show this help message"
	@echo "  info     - Show build configuration"
	@echo ""
	@echo "Build types:"
	@echo "  make BUILD_TYPE=debug   - Debug build with symbols"
	@echo "  make BUILD_TYPE=release - Optimized release build"
	@echo ""
	@echo "Platform: $(UNAME_S)"
	@echo "Compiler: $(CXX)"

# Show build information
info:
	@echo "Build Configuration:"
	@echo "  Compiler: $(CXX)"
	@echo "  Platform: $(UNAME_S)"
	@echo "  Build Type: $(BUILD_TYPE)"
	@echo "  Flags: $(CXXFLAGS)"
	@echo "  Source Files: $(MAIN_SRC) $(LIB_SRC)"
	@echo "  Target: $(TARGET)"

# Phony targets
.PHONY: all clean release debug run test install help info

# Dependencies
$(OBJDIR)/file.o: file.cpp
$(OBJDIR)/StaticLib1.o: StaticLib1.cpp pch.h framework.h
$(OBJDIR)/pch.o: pch.cpp pch.h framework.h
