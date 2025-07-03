/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Core Types Module
 * ============================================================================
 * 
 * This file defines the fundamental data structures and enumerations used
 * throughout the .pong language interpreter. It provides the foundation
 * for value representation, type management, and variable storage.
 * 
 * Core Components:
 * - TokenType: Enumeration of all possible token types in the language
 * - ValueType: Enumeration of supported data types (int, char, string)
 * - Value: Union structure for storing typed values
 * - Variable: Structure representing a named variable with its value
 * - Token: Structure representing a lexical token with metadata
 * 
 * Constants define maximum sizes and error codes for robust error handling.
 * 
 * ============================================================================
 */

#ifndef TYPES_H
    #define TYPES_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_VARIABLE_NAME 256
#define MAX_STRING_LENGTH 1024
#define MAX_IDENTIFIER_LENGTH 256

#define ERROR_SUCCESS 0
#define ERROR_MEMORY_ALLOCATION 1
#define ERROR_INVALID_TYPE 2
#define ERROR_VARIABLE_NOT_FOUND 3
#define ERROR_SYNTAX_ERROR 4
#define ERROR_TYPE_MISMATCH 5

typedef enum {
    TOKEN_INT,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_EOF,
    TOKEN_NEWLINE,
    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_CHAR,
    TOKEN_KEYWORD_STRING,
    TOKEN_NUMBER,
    TOKEN_CHAR_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_UNKNOWN
} TokenType;

typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_STRING
} ValueType;

typedef union {
    int int_val;
    char char_val;
    char* string_val;
} ValueData;

typedef struct {
    ValueType type;
    ValueData data;
} Value;

typedef struct {
    char name[MAX_VARIABLE_NAME];
    Value* value;
} Variable;

typedef union {
    int int_val;
    char char_val;
    char* string_val;
    char* identifier;
} TokenValue;

typedef struct {
    TokenType type;
    TokenValue value;
    int line;
    int column;
} Token;

Value* init_value(ValueType type);
void free_value(Value* val);
Value* copy_value(Value* src);
void print_value(Value* val);

#endif
