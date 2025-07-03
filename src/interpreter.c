/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Execution Engine Implementation
 * ============================================================================
 * 
 * Implementation of the execution engine for the .pong language interpreter.
 * Provides complete statement execution with runtime error handling and
 * environment management for variable operations.
 * 
 * The interpreter processes parsed statements sequentially, maintaining
 * program state and providing comprehensive error reporting. It integrates
 * with all interpreter components for complete program execution.
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

Interpreter* init_interpreter(void) {
    Interpreter* interp = malloc(sizeof(Interpreter));
    if (!interp) {
        return NULL;
    }
    interp->global_env = create_env();
    if (!interp->global_env) {
        free(interp);
        return NULL;
    }
    interp->has_error = false;
    interp->error_message[0] = '\0';
    interp->executed_statements = 0;
    return interp;
}

bool execute_declaration(Interpreter* interp, Statement* stmt) {
    if (!interp || !stmt || stmt->type != STMT_DECLARATION) {
        return false;
    }
    DeclarationStatement* decl = &stmt->data.declaration;
    if (variable_exists(interp->global_env, decl->var_name)) {
        snprintf(interp->error_message, sizeof(interp->error_message),
                "Variable '%s' already declared at line %d",
                decl->var_name, stmt->line);
        interp->has_error = true;
        return false;
    }
    if (!set_variable(interp->global_env, decl->var_name, decl->initial_value)) {
        snprintf(interp->error_message, sizeof(interp->error_message),
                "Failed to declare variable '%s' at line %d",
                decl->var_name, stmt->line);
        interp->has_error = true;
        return false;
    }
    printf("Declared variable '%s' = ", decl->var_name);
    print_value(decl->initial_value);
    printf("\n");
    return true;
}

bool execute_assignment(Interpreter* interp, Statement* stmt) {
    if (!interp || !stmt || stmt->type != STMT_ASSIGNMENT) {
        return false;
    }
    AssignmentStatement* assign = &stmt->data.assignment;
    if (!variable_exists(interp->global_env, assign->var_name)) {
        snprintf(interp->error_message, sizeof(interp->error_message),
                "Undefined variable '%s' at line %d",
                assign->var_name, stmt->line);
        interp->has_error = true;
        return false;
    }
    if (!set_variable(interp->global_env, assign->var_name, assign->new_value)) {
        snprintf(interp->error_message, sizeof(interp->error_message),
                "Failed to assign to variable '%s' at line %d",
                assign->var_name, stmt->line);
        interp->has_error = true;
        return false;
    }
    printf("Assigned variable '%s' = ", assign->var_name);
    print_value(assign->new_value);
    printf("\n");
    return true;
}

bool execute_statement(Interpreter* interp, Statement* stmt) {
    if (!interp || !stmt) {
        return false;
    }
    switch (stmt->type) {
        case STMT_DECLARATION:
            return execute_declaration(interp, stmt);
        case STMT_ASSIGNMENT:
            return execute_assignment(interp, stmt);
        default:
            snprintf(interp->error_message, sizeof(interp->error_message),
                    "Unknown statement type at line %d", stmt->line);
            interp->has_error = true;
            return false;
    }
}

void run(Interpreter* interp, char* source) {
    if (!interp || !source) {
        return;
    }
    Lexer* lexer = init_lexer(source);
    if (!lexer) {
        snprintf(interp->error_message, sizeof(interp->error_message),
                "Failed to initialize lexer");
        interp->has_error = true;
        return;
    }
    Parser* parser = init_parser(lexer, interp->global_env);
    if (!parser) {
        free_lexer(lexer);
        snprintf(interp->error_message, sizeof(interp->error_message),
                "Failed to initialize parser");
        interp->has_error = true;
        return;
    }
    printf("=== PONG INTERPRETER EXECUTION ===\n");
    
    while (parser->current_token && parser->current_token->type != TOKEN_EOF) {
        if (parser->has_error) {
            printf("Parser error: %s\n", parser->error_message);
            break;
        }
        Statement* stmt = parse_statement(parser);
        if (!stmt) {
            if (parser->has_error) {
                printf("Parse error: %s\n", parser->error_message);
            }
            break;
        }
        if (!execute_statement(interp, stmt)) {
            printf("Runtime error: %s\n", interp->error_message);
            free_statement(stmt);
            break;
        }
        interp->executed_statements++;
        free_statement(stmt);
    }
    
    printf("=== EXECUTION COMPLETE ===\n");
    printf("Executed %d statements\n", interp->executed_statements);
    free_parser(parser);
    free_lexer(lexer);
}

void free_interpreter(Interpreter* interp) {
    if (!interp) {
        return;
    }
    if (interp->global_env) {
        free_env(interp->global_env);
    }
    free(interp);
}
