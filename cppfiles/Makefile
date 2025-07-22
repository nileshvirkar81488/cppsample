# Makefile for C++ project
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
DEBUGFLAGS = -g -O0 -D_DEBUG
RELEASEFLAGS = -O2 -DNDEBUG

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

# Build release version
release:
	$(MAKE) BUILD_TYPE=release

# Build debug version
debug:
	$(MAKE) BUILD_TYPE=debug

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean release debug run

# Dependencies
$(OBJDIR)/file.o: file.cpp
$(OBJDIR)/StaticLib1.o: StaticLib1.cpp pch.h framework.h
$(OBJDIR)/pch.o: pch.cpp pch.h framework.h
