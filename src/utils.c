/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Utility Functions Implementation
 * ============================================================================
 * 
 * Implementation of utility functions for the .pong language interpreter.
 * Provides robust file operations, error handling, and memory management
 * with comprehensive error checking and cross-platform compatibility.
 * 
 * File operations support complete source file reading with proper memory
 * management. Error reporting provides formatted output with position
 * information for debugging and user feedback.
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char* read_file(char* filename) {
    if (!filename) {
        return NULL;
    }
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (file_size < 0) {
        fprintf(stderr, "Error: Cannot determine size of file '%s'\n", filename);
        fclose(file);
        return NULL;
    }
    char* content = malloc(file_size + 1);
    if (!content) {
        fprintf(stderr, "Error: Memory allocation failed for file '%s'\n", filename);
        fclose(file);
        return NULL;
    }
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';
    fclose(file);
    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Warning: Expected to read %ld bytes, but read %zu bytes from '%s'\n", 
                file_size, bytes_read, filename);
    }
    return content;
}

void error(char* message, int line, int col) {
    if (!message) {
        return;
    }
    if (line > 0 && col > 0) {
        fprintf(stderr, "Error at line %d, column %d: %s\n", line, col, message);
    } else if (line > 0) {
        fprintf(stderr, "Error at line %d: %s\n", line, message);
    } else {
        fprintf(stderr, "Error: %s\n", message);
    }
}

void* safe_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Fatal error: Memory allocation of %zu bytes failed\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

char* safe_strdup(char* str) {
    if (!str) {
        return NULL;
    }
    size_t len = strlen(str);
    char* copy = safe_malloc(len + 1);
    strcpy(copy, str);
    return copy;
}

void print_usage(char* program_name) {
    if (!program_name) {
        program_name = "pong-interpreter";
    }
    printf("Usage: %s <filename.pong>\n", program_name);
    printf("\n");
    printf("Pong Language Interpreter - Execute .pong source files\n");
    printf("\n");
    printf("Arguments:\n");
    printf("  filename.pong    Path to the .pong source file to execute\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s hello.pong\n", program_name);
    printf("  %s examples/variables.pong\n", program_name);
    printf("\n");
    printf("Supported language features:\n");
    printf("  - Variable declarations: int x = 5;\n");
    printf("  - Variable assignments: x = 10;\n");
    printf("  - Data types: int, char, string\n");
    printf("\n");
}
