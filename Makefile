# Root Makefile for C++ Sample Project
# Author: Generated for cppsample project
# Date: July 31, 2025

# Subdirectories containing projects
SUBDIRS = cppfiles

# Default target
.PHONY: all
all: 
	@echo "Building all C++ projects..."
	@for dir in $(SUBDIRS); do \
		echo "Building in $$dir..."; \
		$(MAKE) -C $$dir || exit 1; \
	done
	@echo "All projects built successfully!"

# Clean all subdirectories
.PHONY: clean
clean:
	@echo "Cleaning all projects..."
	@for dir in $(SUBDIRS); do \
		echo "Cleaning $$dir..."; \
		$(MAKE) -C $$dir clean; \
	done
	@echo "All projects cleaned!"

# Build release versions
.PHONY: release
release:
	@echo "Building release versions..."
	@for dir in $(SUBDIRS); do \
		echo "Building release in $$dir..."; \
		$(MAKE) -C $$dir release || exit 1; \
	done
	@echo "All release builds completed!"

# Build debug versions  
.PHONY: debug
debug:
	@echo "Building debug versions..."
	@for dir in $(SUBDIRS); do \
		echo "Building debug in $$dir..."; \
		$(MAKE) -C $$dir debug || exit 1; \
	done
	@echo "All debug builds completed!"

# Run tests in all subdirectories
.PHONY: test
test:
	@echo "Running tests in all projects..."
	@for dir in $(SUBDIRS); do \
		echo "Testing $$dir..."; \
		$(MAKE) -C $$dir test || echo "Tests failed in $$dir"; \
	done

# Install all projects
.PHONY: install
install:
	@echo "Installing all projects..."
	@for dir in $(SUBDIRS); do \
		echo "Installing from $$dir..."; \
		$(MAKE) -C $$dir install || echo "Install failed in $$dir"; \
	done

# Show help for all projects
.PHONY: help
help:
	@echo "Root Makefile for C++ Sample Project"
	@echo "===================================="
	@echo ""
	@echo "Available targets:"
	@echo "  all      - Build all projects (default)"
	@echo "  clean    - Clean all projects"
	@echo "  debug    - Build debug versions of all projects"
	@echo "  release  - Build release versions of all projects"
	@echo "  test     - Run tests in all projects"
	@echo "  install  - Install all projects"
	@echo "  help     - Show this help message"
	@echo "  info     - Show project information"
	@echo ""
	@echo "Project structure:"
	@echo "  cppfiles/ - Main C++ project with memory analysis examples"
	@echo ""
	@echo "To build a specific project:"
	@echo "  cd cppfiles && make"
	@echo ""
	@echo "To get help for a specific project:"
	@echo "  make -C cppfiles help"

# Show project information
.PHONY: info
info:
	@echo "C++ Sample Project Information"
	@echo "=============================="
	@echo "Root directory: $(shell pwd)"
	@echo "Subdirectories: $(SUBDIRS)"
	@echo "Compiler: $(shell which g++ 2>/dev/null || echo 'g++ not found')"
	@echo "Make version: $(shell make --version | head -n1)"
	@echo ""
	@echo "Project details:"
	@for dir in $(SUBDIRS); do \
		echo "  $$dir/:"; \
		$(MAKE) -C $$dir info 2>/dev/null || echo "    No info available"; \
		echo ""; \
	done

# Target to build specific subdirectory
.PHONY: $(SUBDIRS)
$(SUBDIRS):
	@echo "Building $@..."
	$(MAKE) -C $@

# Target to clean specific subdirectory
.PHONY: $(SUBDIRS:%=%-clean)
$(SUBDIRS:%=%-clean):
	@echo "Cleaning $(patsubst %-clean,%,$@)..."
	$(MAKE) -C $(patsubst %-clean,%,$@) clean