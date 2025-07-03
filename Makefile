# ============================================================================
# PONG LANGUAGE INTERPRETER - Comprehensive Build System
# ============================================================================
# 
# This Makefile provides a complete build system for the .pong language
# interpreter. It includes multiple build configurations, testing,
# debugging, profiling, and development tools for a professional
# development experience.
# 
# Main features:
# - Multiple build configurations (debug, release, profile)
# - Comprehensive testing framework
# - Memory debugging with Valgrind
# - Code analysis and formatting tools
# - Installation and packaging support
# - Development utilities and examples
# 
# ============================================================================

# ============================================================================
# PROJECT CONFIGURATION
# ============================================================================

PROJECT_NAME    := pong-interpreter
VERSION         := 1.0.0
AUTHOR          := guiiireg
DESCRIPTION     := Interpreter for the .pong programming language
REPOSITORY      := https://github.com/guiiireg/Pong.git

# Version scheme:
# - Feature additions: 1.0.0 -> 1.1.0 (minor version bump)
# - Bug fixes: 1.0.0 -> 1.0.1 (patch version bump)
# - Major updates: 1.x.x -> 2.0.0 (major version bump)

# ============================================================================
# DIRECTORY STRUCTURE
# ============================================================================

SRC_DIR         := src
INCLUDE_DIR     := include
BUILD_DIR       := build
LIB_DIR         := lib
TEST_DIR        := tests
EXAMPLE_DIR     := examples
DOCS_DIR        := docs
OBJ_DIR         := $(BUILD_DIR)/obj
BIN_DIR         := $(BUILD_DIR)/bin
COVERAGE_DIR    := $(BUILD_DIR)/coverage

# ============================================================================
# COMPILER AND TOOLS CONFIGURATION
# ============================================================================

CC              := gcc
AR              := ar
RANLIB          := ranlib
VALGRIND        := valgrind
CPPCHECK        := cppcheck
CLANG_FORMAT    := clang-format

# Base compilation flags
CFLAGS_BASE     := -std=c99 -pedantic -Wall -Wextra -Werror
CFLAGS_BASE     += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS_BASE     += -Wold-style-definition -Wmissing-declarations
CFLAGS_BASE     += -Wredundant-decls -Wnested-externs
CFLAGS_BASE     += -I$(INCLUDE_DIR)

# Debug flags
CFLAGS_DEBUG    := $(CFLAGS_BASE) -g3 -O0 -DDEBUG -fsanitize=address
CFLAGS_DEBUG    += -fno-omit-frame-pointer -fstack-protector-strong

# Release flags
CFLAGS_RELEASE  := $(CFLAGS_BASE) -O3 -DNDEBUG -march=native -flto

# Profile flags
CFLAGS_PROFILE  := $(CFLAGS_BASE) -O2 -g -pg -DPROFILE

# Coverage flags
CFLAGS_COVERAGE := $(CFLAGS_DEBUG) --coverage -fprofile-arcs -ftest-coverage

# Default flags
CFLAGS          := $(CFLAGS_DEBUG)

# Linker flags
LDFLAGS         := 
LDFLAGS_DEBUG   := -fsanitize=address
LDFLAGS_COVERAGE:= --coverage

# ============================================================================
# SOURCE FILES CONFIGURATION
# ============================================================================

SOURCES         := $(wildcard $(SRC_DIR)/*.c)
OBJECTS         := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS         := $(wildcard $(INCLUDE_DIR)/*.h)

TEST_SOURCES    := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS    := $(TEST_SOURCES:$(TEST_DIR)/%.c=$(OBJ_DIR)/test_%.o)

EXAMPLE_SOURCES := $(wildcard $(EXAMPLE_DIR)/*.pong)

# Target executable
TARGET          := $(PROJECT_NAME)
TARGET_PATH     := $(BIN_DIR)/$(TARGET)

# ============================================================================
# DEFAULT TARGET
# ============================================================================

.PHONY: all
all: help

# ============================================================================
# HELP SYSTEM
# ============================================================================

.PHONY: help
help:
	@echo "============================================================================"
	@echo "$(PROJECT_NAME) v$(VERSION) - Build System Help"
	@echo "============================================================================"
	@echo ""
	@echo "MAIN TARGETS:"
	@echo "  help              - Show this help message"
	@echo "  build             - Build debug version of the interpreter"
	@echo "  release           - Build optimized release version"
	@echo "  debug             - Build with debug symbols and sanitizers"
	@echo "  profile           - Build with profiling enabled"
	@echo "  clean             - Remove all build artifacts"
	@echo "  distclean         - Complete cleanup including dependencies"
	@echo ""
	@echo "TESTING TARGETS:"
	@echo "  test              - Build and run all tests"
	@echo "  test-build        - Build tests only"
	@echo "  test-run          - Run existing tests"
	@echo "  test-coverage     - Generate code coverage report"
	@echo "  test-examples     - Test all example .pong files"
	@echo ""
	@echo "DEBUGGING TARGETS:"
	@echo "  valgrind          - Run interpreter under Valgrind"
	@echo "  valgrind-test     - Run tests under Valgrind"
	@echo "  gdb               - Debug interpreter with GDB"
	@echo ""
	@echo "ANALYSIS TARGETS:"
	@echo "  analyze           - Run static code analysis"
	@echo "  lint              - Run code linting"
	@echo "  format            - Format code with clang-format"
	@echo "  format-check      - Check code formatting"
	@echo ""
	@echo "INSTALLATION:"
	@echo "  install           - Install to system (/usr/local/bin)"
	@echo "  install-user      - Install to user directory (~/.local/bin)"
	@echo "  uninstall         - Remove installed interpreter"
	@echo ""
	@echo "EXAMPLES:"
	@echo "  run-examples      - Run all example .pong programs"
	@echo "  demo              - Run demonstration of interpreter features"
	@echo ""
	@echo "BUILD CONFIGURATIONS:"
	@echo "  CONFIG=debug      - Debug build (default)"
	@echo "  CONFIG=release    - Release build"
	@echo "  CONFIG=profile    - Profile build"
	@echo "  CONFIG=coverage   - Coverage build"
	@echo ""
	@echo "EXAMPLES:"
	@echo "  make build                    # Build debug interpreter"
	@echo "  make CONFIG=release build     # Build release version"
	@echo "  make test                     # Run all tests"
	@echo "  make run-examples            # Test example programs"
	@echo "  make valgrind simple.pong    # Debug with Valgrind"
	@echo ""
	@echo "============================================================================"

# ============================================================================
# BUILD CONFIGURATION SELECTION
# ============================================================================

ifeq ($(CONFIG), release)
    CFLAGS := $(CFLAGS_RELEASE)
    LDFLAGS := 
    BUILD_TYPE := release
else ifeq ($(CONFIG), profile)
    CFLAGS := $(CFLAGS_PROFILE)
    LDFLAGS := -pg
    BUILD_TYPE := profile
else ifeq ($(CONFIG), coverage)
    CFLAGS := $(CFLAGS_COVERAGE)
    LDFLAGS := $(LDFLAGS_COVERAGE)
    BUILD_TYPE := coverage
else
    CFLAGS := $(CFLAGS_DEBUG)
    LDFLAGS := $(LDFLAGS_DEBUG)
    BUILD_TYPE := debug
endif

# ============================================================================
# DIRECTORY CREATION
# ============================================================================

$(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(DOCS_DIR) $(COVERAGE_DIR):
	@mkdir -p $@

# ============================================================================
# OBJECT FILE COMPILATION
# ============================================================================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling $< ($(BUILD_TYPE))"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling test $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# ============================================================================
# MAIN BUILD TARGETS
# ============================================================================

.PHONY: build
build: $(TARGET_PATH)

$(TARGET_PATH): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking $(TARGET) ($(BUILD_TYPE))"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "✓ Built $(TARGET) successfully"

.PHONY: debug
debug:
	@$(MAKE) CONFIG=debug build
	@echo "✓ Debug build completed"

.PHONY: release
release:
	@$(MAKE) CONFIG=release build
	@echo "✓ Release build completed"

.PHONY: profile
profile:
	@$(MAKE) CONFIG=profile build
	@echo "✓ Profile build completed"

# ============================================================================
# TESTING TARGETS
# ============================================================================

.PHONY: test-build
test-build: build

.PHONY: test-run
test-run: test-build
	@echo "Running interpreter tests:"
	@echo "=========================="
	@if [ -f simple.pong ]; then \
		echo "Testing simple.pong:"; \
		$(TARGET_PATH) simple.pong; \
	fi
	@if [ -f test.pong ]; then \
		echo "Testing test.pong:"; \
		$(TARGET_PATH) test.pong; \
	fi

.PHONY: test
test: test-run

.PHONY: test-examples
test-examples: build
	@echo "Testing all example .pong files:"
	@echo "================================"
	@for file in $(EXAMPLE_SOURCES); do \
		echo "Testing $$file:"; \
		$(TARGET_PATH) $$file || echo "❌ Failed: $$file"; \
		echo ""; \
	done

.PHONY: test-coverage
test-coverage:
	@echo "Generating coverage report:"
	@echo "=========================="
	@$(MAKE) CONFIG=coverage test-run
	@gcov $(SOURCES) -o $(OBJ_DIR)
	@if command -v lcov >/dev/null 2>&1; then \
		lcov --capture --directory . --output-file coverage.info; \
		genhtml coverage.info --output-directory $(COVERAGE_DIR); \
		echo "Coverage report generated in $(COVERAGE_DIR)/index.html"; \
	else \
		echo "lcov not found, coverage files generated in current directory"; \
	fi

# ============================================================================
# DEBUGGING TARGETS
# ============================================================================

.PHONY: valgrind
valgrind: build
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make valgrind FILE=<filename.pong>"; \
	else \
		echo "Running $(FILE) under Valgrind:"; \
		echo "==============================="; \
		$(VALGRIND) --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes $(TARGET_PATH) $(FILE); \
	fi

.PHONY: valgrind-test
valgrind-test: build
	@echo "Running tests under Valgrind:"
	@echo "============================="
	@if [ -f simple.pong ]; then \
		$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET_PATH) simple.pong; \
	fi

.PHONY: gdb
gdb: build
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make gdb FILE=<filename.pong>"; \
	else \
		echo "Starting GDB with $(FILE):"; \
		echo "========================="; \
		gdb --args $(TARGET_PATH) $(FILE); \
	fi

# ============================================================================
# ANALYSIS TARGETS
# ============================================================================

.PHONY: analyze
analyze:
	@echo "Running static analysis:"
	@echo "======================="
	@if command -v $(CPPCHECK) >/dev/null 2>&1; then \
		$(CPPCHECK) --enable=all --std=c99 --platform=unix64 \
		--suppress=missingIncludeSystem $(SRC_DIR)/ $(INCLUDE_DIR)/; \
	else \
		echo "cppcheck not found, skipping static analysis"; \
	fi

.PHONY: lint
lint:
	@echo "Running code linting:"
	@echo "===================="
	@if command -v splint >/dev/null 2>&1; then \
		splint +posixlib -I$(INCLUDE_DIR) $(SOURCES) || true; \
	else \
		echo "splint not found, skipping linting"; \
	fi

.PHONY: format
format:
	@echo "Formatting code:"
	@echo "==============="
	@if command -v $(CLANG_FORMAT) >/dev/null 2>&1; then \
		$(CLANG_FORMAT) -i $(SOURCES) $(HEADERS) $(TEST_SOURCES); \
		echo "✓ Code formatted"; \
	else \
		echo "clang-format not found, skipping formatting"; \
	fi

.PHONY: format-check
format-check:
	@echo "Checking code formatting:"
	@echo "========================"
	@if command -v $(CLANG_FORMAT) >/dev/null 2>&1; then \
		for file in $(SOURCES) $(HEADERS); do \
			if ! $(CLANG_FORMAT) -output-replacements-xml $$file | grep -q "<replacement "; then \
				echo "✓ $$file"; \
			else \
				echo "❌ $$file needs formatting"; \
			fi; \
		done; \
	else \
		echo "clang-format not found, skipping format check"; \
	fi

# ============================================================================
# EXAMPLE AND DEMONSTRATION TARGETS
# ============================================================================

.PHONY: run-examples
run-examples: build
	@echo "Running all example programs:"
	@echo "============================="
	@for file in $(EXAMPLE_SOURCES); do \
		echo "Running $$file:"; \
		echo "---------------"; \
		$(TARGET_PATH) $$file; \
		echo ""; \
	done

.PHONY: demo
demo: build
	@echo "Pong Language Interpreter Demo:"
	@echo "==============================="
	@echo ""
	@echo "1. Simple variable declaration:"
	@$(TARGET_PATH) simple.pong
	@echo ""
	@echo "2. Complex example with multiple types:"
	@$(TARGET_PATH) test.pong
	@echo ""
	@echo "3. Example programs:"
	@$(MAKE) --no-print-directory run-examples

# ============================================================================
# INSTALLATION TARGETS
# ============================================================================

PREFIX ?= /usr/local
USER_PREFIX := $(HOME)/.local

.PHONY: install
install: release
	@echo "Installing to system ($(PREFIX)):"
	@echo "================================="
	@install -d $(PREFIX)/bin
	@install -m 755 $(TARGET_PATH) $(PREFIX)/bin/$(TARGET)
	@echo "✓ Installed $(TARGET) to $(PREFIX)/bin/"

.PHONY: install-user
install-user: release
	@echo "Installing to user directory ($(USER_PREFIX)):"
	@echo "=============================================="
	@install -d $(USER_PREFIX)/bin
	@install -m 755 $(TARGET_PATH) $(USER_PREFIX)/bin/$(TARGET)
	@echo "✓ Installed $(TARGET) to $(USER_PREFIX)/bin/"
	@echo "Note: Make sure $(USER_PREFIX)/bin is in your PATH"

.PHONY: uninstall
uninstall:
	@echo "Uninstalling interpreter:"
	@echo "========================"
	@rm -f $(PREFIX)/bin/$(TARGET)
	@rm -f $(USER_PREFIX)/bin/$(TARGET)
	@echo "✓ Uninstalled $(TARGET)"

# ============================================================================
# CLEANUP TARGETS
# ============================================================================

.PHONY: clean
clean:
	@echo "Cleaning build artifacts:"
	@echo "========================"
	@rm -rf $(BUILD_DIR)
	@rm -f *.gcov *.gcda *.gcno coverage.info
	@echo "✓ Cleanup completed"

.PHONY: distclean
distclean: clean
	@echo "Deep cleaning:"
	@echo "============="
	@rm -rf $(DOCS_DIR)
	@rm -f core vgcore.* *.log
	@echo "✓ Deep cleanup completed"

# ============================================================================
# UTILITY TARGETS
# ============================================================================

.PHONY: info
info:
	@echo "============================================================================"
	@echo "BUILD INFORMATION"
	@echo "============================================================================"
	@echo "Project:        $(PROJECT_NAME) v$(VERSION)"
	@echo "Description:    $(DESCRIPTION)"
	@echo "Author:         $(AUTHOR)"
	@echo "Repository:     $(REPOSITORY)"
	@echo "Build type:     $(BUILD_TYPE)"
	@echo "Compiler:       $(CC)"
	@echo "CFLAGS:         $(CFLAGS)"
	@echo "LDFLAGS:        $(LDFLAGS)"
	@echo "Sources:        $(words $(SOURCES)) files"
	@echo "Headers:        $(words $(HEADERS)) files"
	@echo "Examples:       $(words $(EXAMPLE_SOURCES)) files"
	@echo "============================================================================"

.PHONY: list-targets
list-targets:
	@echo "Available targets:"
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | \
	awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | \
	sort | grep -E "^[a-zA-Z][^$$#/\t=]*$$"

.PHONY: version-info
version-info:
	@echo "Version Information:"
	@echo "==================="
	@echo "Current version: $(VERSION)"
	@echo ""
	@echo "Version scheme:"
	@echo "  Feature additions: x.X.x -> x.(X+1).0"
	@echo "  Bug fixes: x.x.X -> x.x.(X+1)" 
	@echo "  Major updates: X.x.x -> (X+1).0.0"
	@echo ""
	@echo "To update version, edit VERSION in Makefile"

# ============================================================================
# DEPENDENCY TRACKING
# ============================================================================

-include $(OBJECTS:.o=.d)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

# ============================================================================
# SPECIAL TARGETS AND CONFIGURATION
# ============================================================================

.SUFFIXES:
.SECONDARY:
.DELETE_ON_ERROR:

# Phony targets
.PHONY: all build debug release profile test test-build test-run test-examples
.PHONY: test-coverage valgrind valgrind-test gdb analyze lint format format-check
.PHONY: run-examples demo install install-user uninstall clean distclean
.PHONY: info list-targets help version-info

# Special variables
.DEFAULT_GOAL := help
MAKEFLAGS += --no-print-directory
