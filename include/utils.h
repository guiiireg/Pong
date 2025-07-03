/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Utility Functions Module
 * ============================================================================
 * 
 * This module provides essential utility functions for the .pong language
 * interpreter. It includes file I/O operations, error handling utilities,
 * and memory management helpers to support robust interpreter operation.
 * 
 * Core Functionality:
 * - File reading operations for .pong source files
 * - Standardized error reporting with position information
 * - Memory allocation wrappers with error checking
 * - String duplication with validation
 * - Cross-platform compatibility helpers
 * 
 * These utilities ensure consistent error handling and memory management
 * throughout the interpreter, improving reliability and debugging capabilities.
 * 
 * ============================================================================
 */

#ifndef UTILS_H
    #define UTILS_H

#include <stddef.h>

char* read_file(char* filename);
void error(char* message, int line, int col);
void* safe_malloc(size_t size);
char* safe_strdup(char* str);
void print_usage(char* program_name);

#endif
