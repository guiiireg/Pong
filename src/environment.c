/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Environment Management Implementation
 * ============================================================================
 * 
 * Implementation of the runtime environment for the .pong language interpreter.
 * Provides complete variable lifecycle management with efficient storage,
 * retrieval, and memory management using a linked list data structure.
 * 
 * Variable operations support both creation of new variables and modification
 * of existing ones. The implementation ensures proper memory cleanup and
 * provides fast existence checking for parser optimization.
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"

Environment* create_env(void) {
    Environment* env = malloc(sizeof(Environment));
    if (!env) {
        return NULL;
    }
    env->variables = NULL;
    env->count = 0;
    return env;
}

void free_env(Environment* env) {
    if (!env) {
        return;
    }
    VariableNode* current = env->variables;
    while (current) {
        VariableNode* next = current->next;
        
        if (current->variable) {
            free_value(current->variable->value);
            free(current->variable);
        }
        free(current);
        
        current = next;
    }
    free(env);
}

bool set_variable(Environment* env, char* name, Value* value) {
    if (!env || !name || !value) {
        return false;
    }
    VariableNode* current = env->variables;
    while (current) {
        if (strcmp(current->variable->name, name) == 0) {
            free_value(current->variable->value);
            current->variable->value = copy_value(value);
            return current->variable->value != NULL;
        }
        current = current->next;
    }
    VariableNode* new_node = malloc(sizeof(VariableNode));
    if (!new_node) {
        return false;
    }
    Variable* new_var = malloc(sizeof(Variable));
    if (!new_var) {
        free(new_node);
        return false;
    }
    strncpy(new_var->name, name, MAX_VARIABLE_NAME - 1);
    new_var->name[MAX_VARIABLE_NAME - 1] = '\0';
    new_var->value = copy_value(value);
    if (!new_var->value) {
        free(new_var);
        free(new_node);
        return false;
    }
    new_node->variable = new_var;
    new_node->next = env->variables;
    env->variables = new_node;
    env->count++;
    return true;
}

Value* get_variable(Environment* env, char* name) {
    if (!env || !name) {
        return NULL;
    }
    VariableNode* current = env->variables;
    while (current) {
        if (strcmp(current->variable->name, name) == 0) {
            return current->variable->value;
        }
        current = current->next;
    }
    return NULL;
}

bool variable_exists(Environment* env, char* name) {
    if (!env || !name) {
        return false;
    }
    VariableNode* current = env->variables;
    while (current) {
        if (strcmp(current->variable->name, name) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}
