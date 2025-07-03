/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Syntax Analysis Implementation
 * ============================================================================
 * 
 * Implementation of the parser for the .pong language interpreter. Provides
 * complete syntax analysis with error handling and AST construction for
 * variable declarations and assignments.
 * 
 * The parser uses recursive descent parsing techniques to process tokens
 * and build statement structures. It validates syntax according to language
 * grammar rules and provides detailed error reporting for debugging.
 * 
 * ============================================================================
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

Parser* init_parser(Lexer* lexer, Environment* env) {
    if (!lexer || !env) {
        return NULL;
    }
    Parser* parser = malloc(sizeof(Parser));
    if (!parser) {
        return NULL;
    }
    parser->lexer = lexer;
    parser->env = env;
    parser->has_error = false;
    parser->error_message[0] = '\0';
    parser->current_token = next_token(lexer);
    return parser;
}

void advance_token(Parser* parser) {
    if (!parser) {
        return;
    }
    if (parser->current_token) {
        free_token(parser->current_token);
    }
    parser->current_token = next_token(parser->lexer);
}

bool expect_token(Parser* parser, TokenType expected) {
    if (!parser || !parser->current_token) {
        return false;
    }
    if (parser->current_token->type != expected) {
        snprintf(parser->error_message, sizeof(parser->error_message),
                "Expected token type %d, got %d at line %d, column %d",
                expected, parser->current_token->type,
                parser->current_token->line, parser->current_token->column);
        parser->has_error = true;
        return false;
    }
    return true;
}

Statement* parse_declaration(Parser* parser) {
    if (!parser || !parser->current_token) {
        return NULL;
    }
    Statement* stmt = malloc(sizeof(Statement));
    if (!stmt) {
        return NULL;
    }
    stmt->type = STMT_DECLARATION;
    stmt->line = parser->current_token->line;
    stmt->column = parser->current_token->column;
    ValueType var_type;
    switch (parser->current_token->type) {
        case TOKEN_KEYWORD_INT:
            var_type = TYPE_INT;
            break;
        case TOKEN_KEYWORD_CHAR:
            var_type = TYPE_CHAR;
            break;
        case TOKEN_KEYWORD_STRING:
            var_type = TYPE_STRING;
            break;
        default:
            free(stmt);
            return NULL;
    }
    advance_token(parser);
    if (!expect_token(parser, TOKEN_IDENTIFIER)) {
        free(stmt);
        return NULL;
    }
    stmt->data.declaration.var_name = strdup(parser->current_token->value.string_val);
    stmt->data.declaration.var_type = var_type;
    advance_token(parser);
    if (!expect_token(parser, TOKEN_ASSIGN)) {
        free(stmt->data.declaration.var_name);
        free(stmt);
        return NULL;
    }
    advance_token(parser);
    Value* initial_value = init_value(var_type);
    if (!initial_value) {
        free(stmt->data.declaration.var_name);
        free(stmt);
        return NULL;
    }
    switch (var_type) {
        case TYPE_INT:
            if (!expect_token(parser, TOKEN_NUMBER)) {
                free_value(initial_value);
                free(stmt->data.declaration.var_name);
                free(stmt);
                return NULL;
            }
            initial_value->data.int_val = parser->current_token->value.int_val;
            break;
        case TYPE_CHAR:
            if (!expect_token(parser, TOKEN_CHAR_LITERAL)) {
                free_value(initial_value);
                free(stmt->data.declaration.var_name);
                free(stmt);
                return NULL;
            }
            initial_value->data.char_val = parser->current_token->value.char_val;
            break;
        case TYPE_STRING:
            if (!expect_token(parser, TOKEN_STRING_LITERAL)) {
                free_value(initial_value);
                free(stmt->data.declaration.var_name);
                free(stmt);
                return NULL;
            }
            initial_value->data.string_val = strdup(parser->current_token->value.string_val);
            break;
    }
    stmt->data.declaration.initial_value = initial_value;
    advance_token(parser);
    if (!expect_token(parser, TOKEN_SEMICOLON)) {
        free_value(initial_value);
        free(stmt->data.declaration.var_name);
        free(stmt);
        return NULL;
    }
    advance_token(parser);
    return stmt;
}

Statement* parse_assignment(Parser* parser) {
    if (!parser || !parser->current_token) {
        return NULL;
    }
    Statement* stmt = malloc(sizeof(Statement));
    if (!stmt) {
        return NULL;
    }
    stmt->type = STMT_ASSIGNMENT;
    stmt->line = parser->current_token->line;
    stmt->column = parser->current_token->column;
    if (!expect_token(parser, TOKEN_IDENTIFIER)) {
        free(stmt);
        return NULL;
    }
    stmt->data.assignment.var_name = strdup(parser->current_token->value.string_val);
    advance_token(parser);
    if (!expect_token(parser, TOKEN_ASSIGN)) {
        free(stmt->data.assignment.var_name);
        free(stmt);
        return NULL;
    }
    advance_token(parser);
    Value* existing_var = get_variable(parser->env, stmt->data.assignment.var_name);
    if (!existing_var) {
        snprintf(parser->error_message, sizeof(parser->error_message),
                "Undefined variable '%s' at line %d", 
                stmt->data.assignment.var_name, stmt->line);
        parser->has_error = true;
        free(stmt->data.assignment.var_name);
        free(stmt);
        return NULL;
    }
    Value* new_value = init_value(existing_var->type);
    if (!new_value) {
        free(stmt->data.assignment.var_name);
        free(stmt);
        return NULL;
    }
    switch (existing_var->type) {
        case TYPE_INT:
            if (!expect_token(parser, TOKEN_NUMBER)) {
                free_value(new_value);
                free(stmt->data.assignment.var_name);
                free(stmt);
                return NULL;
            }
            new_value->data.int_val = parser->current_token->value.int_val;
            break;
        case TYPE_CHAR:
            if (!expect_token(parser, TOKEN_CHAR_LITERAL)) {
                free_value(new_value);
                free(stmt->data.assignment.var_name);
                free(stmt);
                return NULL;
            }
            new_value->data.char_val = parser->current_token->value.char_val;
            break;
        case TYPE_STRING:
            if (!expect_token(parser, TOKEN_STRING_LITERAL)) {
                free_value(new_value);
                free(stmt->data.assignment.var_name);
                free(stmt);
                return NULL;
            }
            new_value->data.string_val = strdup(parser->current_token->value.string_val);
            break;
    }
    stmt->data.assignment.new_value = new_value;
    advance_token(parser);
    if (!expect_token(parser, TOKEN_SEMICOLON)) {
        free_value(new_value);
        free(stmt->data.assignment.var_name);
        free(stmt);
        return NULL;
    }
    advance_token(parser);
    return stmt;
}

Statement* parse_statement(Parser* parser) {
    if (!parser || !parser->current_token) {
        return NULL;
    }
    switch (parser->current_token->type) {
        case TOKEN_KEYWORD_INT:
        case TOKEN_KEYWORD_CHAR:
        case TOKEN_KEYWORD_STRING:
            return parse_declaration(parser);
        case TOKEN_IDENTIFIER:
            return parse_assignment(parser);
        default:
            snprintf(parser->error_message, sizeof(parser->error_message),
                    "Unexpected token at line %d, column %d",
                    parser->current_token->line, parser->current_token->column);
            parser->has_error = true;
            return NULL;
    }
}

void free_statement(Statement* stmt) {
    if (!stmt) {
        return;
    }
    switch (stmt->type) {
        case STMT_DECLARATION:
            if (stmt->data.declaration.var_name) {
                free(stmt->data.declaration.var_name);
            }
            if (stmt->data.declaration.initial_value) {
                free_value(stmt->data.declaration.initial_value);
            }
            break;
        case STMT_ASSIGNMENT:
            if (stmt->data.assignment.var_name) {
                free(stmt->data.assignment.var_name);
            }
            if (stmt->data.assignment.new_value) {
                free_value(stmt->data.assignment.new_value);
            }
            break;
        default:
            break;
    }
    free(stmt);
}

void free_parser(Parser* parser) {
    if (!parser) {
        return;
    }
    if (parser->current_token) {
        free_token(parser->current_token);
    }
    free(parser);
}
