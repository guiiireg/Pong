/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Lexical Analysis Module
 * ============================================================================
 * 
 * This module implements the lexical analyzer (lexer) for the .pong language.
 * It transforms raw source code into a stream of tokens for parsing,
 * handling all language constructs including literals, identifiers, and operators.
 * 
 * Core Functionality:
 * - Source code tokenization with position tracking
 * - Character-by-character parsing with lookahead
 * - String literal parsing with escape sequence support
 * - Whitespace and comment handling
 * - Comprehensive token generation for all language elements
 * 
 * The lexer maintains accurate line and column information for error reporting
 * and debugging purposes throughout the tokenization process.
 * 
 * ============================================================================
 */

#ifndef LEXER_H
    #define LEXER_H

#include "token.h"

typedef struct {
    char* source;
    size_t position;
    size_t length;
    int line;
    int column;
} Lexer;

Lexer* init_lexer(char* source);
char next_char(Lexer* lexer);
void skip_whitespace(Lexer* lexer);
char* read_string(Lexer* lexer);
Token* next_token(Lexer* lexer);
void free_lexer(Lexer* lexer);

#endif
