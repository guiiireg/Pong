/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Environment Management Module
 * ============================================================================
 * 
 * This module implements the runtime environment for variable storage and
 * management in the .pong language interpreter. It provides a symbol table
 * implementation for tracking variable names, types, and values during
 * program execution.
 * 
 * Core Functionality:
 * - Dynamic variable storage with efficient lookup
 * - Variable creation, modification, and deletion
 * - Memory-safe environment management with proper cleanup
 * - Variable existence checking for optimization
 * - Support for variable scoping (future extension point)
 * 
 * The environment uses a simple linked list implementation for variable
 * storage, providing O(n) lookup but excellent memory efficiency.
 * 
 * ============================================================================
 */

    #ifndef ENVIRONMENT_H
    #define ENVIRONMENT_H

#include "types.h"

typedef struct VariableNode {
    Variable* variable;
    struct VariableNode* next;
} VariableNode;

typedef struct {
    VariableNode* variables;
    size_t count;
} Environment;

Environment* create_env(void);
void free_env(Environment* env);
bool set_variable(Environment* env, char* name, Value* value);
Value* get_variable(Environment* env, char* name);
bool variable_exists(Environment* env, char* name);

#endif
