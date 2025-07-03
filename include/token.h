/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Token Management Module
 * ============================================================================
 * 
 * This module provides comprehensive token management functionality for the
 * .pong language lexical analysis. It extends the basic Token structure
 * with creation, destruction, and utility functions.
 * 
 * Core Functionality:
 * - Token creation with automatic value copying based on type
 * - Memory-safe token destruction with proper cleanup
 * - Debug-friendly token printing with position information
 * - Keyword recognition for language reserved words
 * 
 * The module handles all token types defined in the language grammar,
 * including literals, identifiers, operators, and keywords.
 * 
 * ============================================================================
 */

#ifndef TOKEN_H
    #define TOKEN_H

#include "types.h"

Token* create_token(TokenType type, void* value, int line, int col);
void free_token(Token* token);
void print_token(Token* token);
bool is_keyword(char* str);

#endif
