/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Execution Engine Module
 * ============================================================================
 * 
 * This module implements the execution engine for the .pong language
 * interpreter. It processes parsed statements and manages program execution
 * state, including variable declarations, assignments, and runtime
 * environment management.
 * 
 * Core Functionality:
 * - Statement execution with proper error handling
 * - Variable declaration processing and environment updates
 * - Assignment execution with type checking
 * - Runtime state management and cleanup
 * - Integration with parser for complete program execution
 * 
 * The interpreter maintains execution context and provides comprehensive
 * error reporting for runtime issues and semantic violations.
 * 
 * ============================================================================
 */

#ifndef INTERPRETER_H
    #define INTERPRETER_H

#include "parser.h"
#include "environment.h"

typedef struct {
    Environment* global_env;
    bool has_error;
    char error_message[256];
    int executed_statements;
} Interpreter;

Interpreter* init_interpreter(void);
bool execute_declaration(Interpreter* interp, Statement* stmt);
bool execute_assignment(Interpreter* interp, Statement* stmt);
bool execute_statement(Interpreter* interp, Statement* stmt);
void run(Interpreter* interp, char* source);
void free_interpreter(Interpreter* interp);

#endif
