/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Syntax Analysis Module
 * ============================================================================
 * 
 * This module implements the parser for the .pong language, responsible for
 * syntax analysis and Abstract Syntax Tree (AST) construction. It processes
 * the token stream from the lexer and builds structured representations
 * of program statements for execution.
 * 
 * Core Functionality:
 * - Recursive descent parsing for language constructs
 * - Variable declaration parsing with type checking
 * - Assignment statement parsing and validation
 * - Syntax error detection and reporting
 * - AST node creation for interpreter execution
 * 
 * The parser maintains current token state and provides lookahead
 * capabilities for complex parsing decisions and error recovery.
 * 
 * ============================================================================
 */

#ifndef PARSER_H
    #define PARSER_H

#include "lexer.h"
#include "environment.h"

typedef enum {
    STMT_DECLARATION,
    STMT_ASSIGNMENT,
    STMT_EXPRESSION
} StatementType;

typedef struct {
    char* var_name;
    ValueType var_type;
    Value* initial_value;
} DeclarationStatement;

typedef struct {
    char* var_name;
    Value* new_value;
} AssignmentStatement;

typedef union {
    DeclarationStatement declaration;
    AssignmentStatement assignment;
} StatementData;

typedef struct {
    StatementType type;
    StatementData data;
    int line;
    int column;
} Statement;

typedef struct {
    Lexer* lexer;
    Token* current_token;
    Environment* env;
    bool has_error;
    char error_message[256];
} Parser;

Parser* init_parser(Lexer* lexer, Environment* env);
Statement* parse_declaration(Parser* parser);
Statement* parse_assignment(Parser* parser);
bool expect_token(Parser* parser, TokenType expected);
void advance_token(Parser* parser);
Statement* parse_statement(Parser* parser);
void free_parser(Parser* parser);
void free_statement(Statement* stmt);

#endif
