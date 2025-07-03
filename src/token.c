/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Token Management Implementation
 * ============================================================================
 * 
 * Implementation of token lifecycle management for the .pong language
 * interpreter. Provides robust token creation, destruction, and utility
 * functions with proper memory management and type-specific handling.
 * 
 * Token creation automatically handles value copying based on token type,
 * ensuring proper memory isolation. Debug printing includes position
 * information for error reporting and development assistance.
 * 
 * ============================================================================
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

Token* create_token(TokenType type, void* value, int line, int col) {
    Token* token = malloc(sizeof(Token));
    if (!token) {
        return NULL;
    }
    token->type = type;
    token->line = line;
    token->column = col;
    switch (type) {
        case TOKEN_NUMBER:
        case TOKEN_INT:
            if (value) {
                token->value.int_val = *(int*)value;
            } else {
                token->value.int_val = 0;
            }
            break;
        case TOKEN_CHAR_LITERAL:
        case TOKEN_CHAR:
            if (value) {
                token->value.char_val = *(char*)value;
            } else {
                token->value.char_val = '\0';
            }
            break;
        case TOKEN_STRING_LITERAL:
        case TOKEN_STRING:
        case TOKEN_IDENTIFIER:
            if (value) {
                token->value.string_val = strdup((char*)value);
                if (!token->value.string_val) {
                    free(token);
                    return NULL;
                }
            } else {
                token->value.string_val = NULL;
            }
            break;
        default:
            token->value.int_val = 0;
            break;
    }
    return token;
}

void free_token(Token* token) {
    if (!token) {
        return;
    }
    switch (token->type) {
        case TOKEN_STRING_LITERAL:
        case TOKEN_STRING:
        case TOKEN_IDENTIFIER:
            if (token->value.string_val) {
                free(token->value.string_val);
            }
            break;
        default:
            break;
    }
    free(token);
}

void print_token(Token* token) {
    if (!token) {
        printf("NULL TOKEN");
        return;
    }
    printf("TOKEN:");
    switch (token->type) {
        case TOKEN_INT:
        case TOKEN_NUMBER:
            printf("INT:%d", token->value.int_val);
            break;
        case TOKEN_CHAR:
        case TOKEN_CHAR_LITERAL:
            printf("CHAR:'%c'", token->value.char_val);
            break;
        case TOKEN_STRING:
        case TOKEN_STRING_LITERAL:
            printf("STRING:\"%s\"", token->value.string_val ? token->value.string_val : "");
            break;
        case TOKEN_IDENTIFIER:
            printf("ID:%s", token->value.string_val ? token->value.string_val : "");
            break;
        case TOKEN_ASSIGN:
            printf("ASSIGN");
            break;
        case TOKEN_SEMICOLON:
            printf("SEMICOLON");
            break;
        case TOKEN_EQUALS:
            printf("EQUALS");
            break;
        case TOKEN_KEYWORD_INT:
            printf("KEYWORD:int");
            break;
        case TOKEN_KEYWORD_CHAR:
            printf("KEYWORD:char");
            break;
        case TOKEN_KEYWORD_STRING:
            printf("KEYWORD:string");
            break;
        case TOKEN_EOF:
            printf("EOF");
            break;
        default:
            printf("UNKNOWN");
            break;
    }
    printf("@%d:%d", token->line, token->column);
}

bool is_keyword(char* str) {
    if (!str) {
        return false;
    }
    return (strcmp(str, "int") == 0 || 
            strcmp(str, "char") == 0 || 
            strcmp(str, "string") == 0);
}
