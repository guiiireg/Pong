/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Lexical Analysis Implementation
 * ============================================================================
 * 
 * Implementation of the lexical analyzer for the .pong language interpreter.
 * Provides complete tokenization of source code with robust error handling
 * and position tracking for comprehensive language support.
 * 
 * The lexer processes source code character by character, identifying
 * language constructs and converting them to tokens. It handles all
 * data types, operators, keywords, and maintains precise source position
 * information for error reporting and debugging.
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Lexer* init_lexer(char* source) {
    if (!source) {
        return NULL;
    }
    Lexer* lexer = malloc(sizeof(Lexer));
    if (!lexer) {
        return NULL;
    }
    lexer->source = source;
    lexer->position = 0;
    lexer->length = strlen(source);
    lexer->line = 1;
    lexer->column = 1;
    return lexer;
}

char next_char(Lexer* lexer) {
    if (!lexer || lexer->position >= lexer->length) {
        return '\0';
    }
    char current = lexer->source[lexer->position];
    lexer->position++;
    if (current == '\n') {
        lexer->line++;
        lexer->column = 1;
    } else {
        lexer->column++;
    }
    return current;
}

void skip_whitespace(Lexer* lexer) {
    if (!lexer) {
        return;
    }
    while (lexer->position < lexer->length) {
        char current = lexer->source[lexer->position];
        if (isspace(current)) {
            next_char(lexer);
        } else {
            break;
        }
    }
}

char* read_string(Lexer* lexer) {
    if (!lexer) {
        return NULL;
    }
    char* buffer = malloc(MAX_STRING_LENGTH);
    if (!buffer) {
        return NULL;
    }
    size_t index = 0;
    char current;
    
    next_char(lexer);
    
    while (lexer->position < lexer->length && index < MAX_STRING_LENGTH - 1) {
        current = lexer->source[lexer->position];
        if (current == '"') {
            next_char(lexer);
            break;
        }
        if (current == '\\' && lexer->position + 1 < lexer->length) {
            next_char(lexer);
            char escaped = lexer->source[lexer->position];
            switch (escaped) {
                case 'n':
                    buffer[index++] = '\n';
                    break;
                case 't':
                    buffer[index++] = '\t';
                    break;
                case 'r':
                    buffer[index++] = '\r';
                    break;
                case '\\':
                    buffer[index++] = '\\';
                    break;
                case '"':
                    buffer[index++] = '"';
                    break;
                default:
                    buffer[index++] = escaped;
                    break;
            }
            next_char(lexer);
        } else {
            buffer[index++] = current;
            next_char(lexer);
        }
    }
    
    buffer[index] = '\0';
    return buffer;
}

Token* next_token(Lexer* lexer) {
    if (!lexer) {
        return NULL;
    }
    skip_whitespace(lexer);
    if (lexer->position >= lexer->length) {
        return create_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
    }
    char current = lexer->source[lexer->position];
    int start_line = lexer->line;
    int start_col = lexer->column;
    if (isdigit(current)) {
        int start_pos = lexer->position;
        while (lexer->position < lexer->length && isdigit(lexer->source[lexer->position])) {
            next_char(lexer);
        }
        char* num_str = malloc(lexer->position - start_pos + 1);
        strncpy(num_str, lexer->source + start_pos, lexer->position - start_pos);
        num_str[lexer->position - start_pos] = '\0';
        int value = atoi(num_str);
        free(num_str);
        return create_token(TOKEN_NUMBER, &value, start_line, start_col);
    }
    if (isalpha(current) || current == '_') {
        int start_pos = lexer->position;
        while (lexer->position < lexer->length && 
               (isalnum(lexer->source[lexer->position]) || lexer->source[lexer->position] == '_')) {
            next_char(lexer);
        }
        char* identifier = malloc(lexer->position - start_pos + 1);
        strncpy(identifier, lexer->source + start_pos, lexer->position - start_pos);
        identifier[lexer->position - start_pos] = '\0';
        TokenType type = TOKEN_IDENTIFIER;
        if (strcmp(identifier, "int") == 0) {
            type = TOKEN_KEYWORD_INT;
        } else if (strcmp(identifier, "char") == 0) {
            type = TOKEN_KEYWORD_CHAR;
        } else if (strcmp(identifier, "string") == 0) {
            type = TOKEN_KEYWORD_STRING;
        }
        Token* token = create_token(type, identifier, start_line, start_col);
        free(identifier);
        return token;
    }
    
    if (current == '"') {
        char* string_val = read_string(lexer);
        Token* token = create_token(TOKEN_STRING_LITERAL, string_val, start_line, start_col);
        free(string_val);
        return token;
    }
    
    if (current == '\'') {
        next_char(lexer);
        if (lexer->position < lexer->length) {
            char char_val = lexer->source[lexer->position];
            next_char(lexer);
            if (lexer->position < lexer->length && lexer->source[lexer->position] == '\'') {
                next_char(lexer);
                return create_token(TOKEN_CHAR_LITERAL, &char_val, start_line, start_col);
            }
        }
    }
    switch (current) {
        case '=':
            next_char(lexer);
            return create_token(TOKEN_ASSIGN, NULL, start_line, start_col);
        case ';':
            next_char(lexer);
            return create_token(TOKEN_SEMICOLON, NULL, start_line, start_col);
        case '+':
            next_char(lexer);
            return create_token(TOKEN_PLUS, NULL, start_line, start_col);
        case '-':
            next_char(lexer);
            return create_token(TOKEN_MINUS, NULL, start_line, start_col);
        case '*':
            next_char(lexer);
            return create_token(TOKEN_MULTIPLY, NULL, start_line, start_col);
        case '/':
            next_char(lexer);
            return create_token(TOKEN_DIVIDE, NULL, start_line, start_col);
        case '(':
            next_char(lexer);
            return create_token(TOKEN_LPAREN, NULL, start_line, start_col);
        case ')':
            next_char(lexer);
            return create_token(TOKEN_RPAREN, NULL, start_line, start_col);
        case '{':
            next_char(lexer);
            return create_token(TOKEN_LBRACE, NULL, start_line, start_col);
        case '}':
            next_char(lexer);
            return create_token(TOKEN_RBRACE, NULL, start_line, start_col);
        default:
            next_char(lexer);
            return create_token(TOKEN_UNKNOWN, NULL, start_line, start_col);
    }
}

void free_lexer(Lexer* lexer) {
    if (lexer) {
        free(lexer);
    }
}
