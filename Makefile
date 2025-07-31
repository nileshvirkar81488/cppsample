# Makefile for C++ Sample Project
# Author: Generated for cppsample project
# Date: July 31, 2025

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -I.

# Qt-specific settings (uncomment if Qt dependencies are available)
# QT_CXXFLAGS = $(shell pkg-config --cflags Qt5Core Qt5Widgets)
# QT_LDFLAGS = $(shell pkg-config --libs Qt5Core Qt5Widgets)

# Debug and Release flags
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Default to debug build
CXXFLAGS += $(DEBUG_FLAGS)

# Directories
SRC_DIR = .
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files that can be built (without missing dependencies)
BUILDABLE_SRCS = malloc_violation.cpp main.cpp
BUILDABLE_OBJS = $(BUILDABLE_SRCS:%.cpp=$(OBJ_DIR)/%.o)
BUILDABLE_TARGETS = $(BUILDABLE_SRCS:%.cpp=$(BUILD_DIR)/%)

# Additional object files needed for main
FAULTHANDLER_OBJ = $(OBJ_DIR)/FaultHandler.o

# Source files with missing dependencies (commented out)
# These require additional setup:
# - datetimecontroller.cpp: needs Qt libraries and TimeZoneModel implementation

# Object files for potentially buildable sources (when dependencies are resolved)
ALL_SRCS = main.cpp datetimecontroller.cpp malloc_violation.cpp
ALL_OBJS = $(ALL_SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Default target
.DEFAULT_GOAL := all

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build all available targets
.PHONY: all
all: $(BUILD_DIR) $(BUILDABLE_TARGETS)
	@echo "Build complete. The following executables are available:"
	@echo "- malloc_violation: Demonstrates C++ memory management violations"
	@echo "- main: FaultHandler simulation program"
	@echo ""
	@echo "Note: The following files have missing dependencies and cannot be built yet:"
	@echo "- datetimecontroller.cpp: Requires Qt libraries and TimeZoneModel implementation"

# Rule to build malloc_violation executable
$(BUILD_DIR)/malloc_violation: $(OBJ_DIR)/malloc_violation.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Rule to build main executable
$(BUILD_DIR)/main: $(OBJ_DIR)/main.o $(FAULTHANDLER_OBJ) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Generic rule for object files
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special rule for FaultHandler
$(FAULTHANDLER_OBJ): FaultHandler.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special targets for files with dependencies (will fail until dependencies are resolved)
.PHONY: main-target
main-target: $(BUILD_DIR)/main
	@echo "Built main executable"

.PHONY: datetime
datetime: $(BUILD_DIR)/datetimecontroller
	@echo "Built datetime controller (requires Qt libraries)"

# Note: This will fail until Qt is properly configured and TimeZoneModel is implemented
$(BUILD_DIR)/datetimecontroller: $(OBJ_DIR)/datetimecontroller.o | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(QT_CXXFLAGS) $< $(QT_LDFLAGS) -o $@

# Test target - runs the buildable executables
.PHONY: test
test: $(BUILDABLE_TARGETS)
	@echo "Running malloc_violation test..."
	./$(BUILD_DIR)/malloc_violation
	@echo ""
	@echo "Running main (FaultHandler) test..."
	./$(BUILD_DIR)/main

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned"

# Install target (installs to /usr/local/bin)
.PHONY: install
install: $(BUILDABLE_TARGETS)
	@echo "Installing executables to /usr/local/bin..."
	sudo cp $(BUILDABLE_TARGETS) /usr/local/bin/
	@echo "Installation complete"

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all      - Build all available executables (default)"
	@echo "  main     - Build main executable (requires FaultHandler implementation)"
	@echo "  datetime - Build datetime controller (requires Qt setup)"
	@echo "  test     - Run available test executables"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install executables to /usr/local/bin"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Build modes:"
	@echo "  make DEBUG=1    - Build with debug flags (default)"
	@echo "  make RELEASE=1  - Build with optimization flags"
	@echo ""
	@echo "Current status:"
	@echo "  ✓ malloc_violation.cpp - Ready to build"
	@echo "  ✓ main.cpp - Ready to build (with FaultHandler implementation)"
	@echo "  ✗ datetimecontroller.cpp - Missing Qt setup and TimeZoneModel"

# Release build
.PHONY: release
release:
	$(MAKE) CXXFLAGS="$(CXXFLAGS:$(DEBUG_FLAGS)=$(RELEASE_FLAGS))"

# Debug build (explicit)
.PHONY: debug
debug:
	$(MAKE) CXXFLAGS="$(CXXFLAGS) $(DEBUG_FLAGS)"

# Show compiler and flags info
.PHONY: info
info:
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Source files: $(ALL_SRCS)"
	@echo "Buildable sources: $(BUILDABLE_SRCS)"
	@echo "Build directory: $(BUILD_DIR)"
