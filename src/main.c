/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Main Entry Point
 * ============================================================================
 * 
 * This is the main entry point for the .pong language interpreter. It handles
 * command-line argument processing, file loading, interpreter initialization,
 * and program execution coordination. The main function orchestrates all
 * interpreter components for complete program execution.
 * 
 * Core Functionality:
 * - Command-line argument validation and processing
 * - Source file loading and validation
 * - Interpreter initialization and execution
 * - Comprehensive cleanup and error handling
 * - User-friendly error messages and usage information
 * 
 * The main function provides the complete interpreter experience from
 * source file to execution results with proper resource management.
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "utils.h"

static void cleanup(Interpreter* interp, char* source_code);

static void cleanup(Interpreter* interp, char* source_code) {
    if (interp) {
        free_interpreter(interp);
    }
    if (source_code) {
        free(source_code);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    char* filename = argv[1];
    if (!filename || strlen(filename) == 0) {
        error("Invalid filename provided", 0, 0);
        return EXIT_FAILURE;
    }
    size_t filename_len = strlen(filename);
    if (filename_len < 5 || strcmp(filename + filename_len - 5, ".pong") != 0) {
        error("File must have .pong extension", 0, 0);
        return EXIT_FAILURE;
    }
    printf("Pong Language Interpreter v1.0\n");
    printf("Loading file: %s\n", filename);
    printf("================================\n\n");
    char* source_code = read_file(filename);
    if (!source_code) {
        error("Failed to read source file", 0, 0);
        return EXIT_FAILURE;
    }
    if (strlen(source_code) == 0) {
        printf("Warning: Source file is empty\n");
        free(source_code);
        return EXIT_SUCCESS;
    }
    Interpreter* interp = init_interpreter();
    if (!interp) {
        error("Failed to initialize interpreter", 0, 0);
        free(source_code);
        return EXIT_FAILURE;
    }
    run(interp, source_code);
    if (interp->has_error) {
        printf("\nExecution failed with error: %s\n", interp->error_message);
        cleanup(interp, source_code);
        return EXIT_FAILURE;
    }
    printf("\nProgram executed successfully!\n");
    cleanup(interp, source_code);
    return EXIT_SUCCESS;
}
