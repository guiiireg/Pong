/**
 * ============================================================================
 * PONG LANGUAGE INTERPRETER - Core Types Implementation
 * ============================================================================
 * 
 * Implementation of fundamental data structure operations for the .pong
 * language interpreter. Provides memory-safe value creation, copying,
 * and destruction with proper handling of dynamic string allocation.
 * 
 * Functions handle the complete lifecycle of Value structures:
 * - Initialization with type-specific default values
 * - Deep copying with proper string duplication
 * - Safe memory deallocation
 * - Debug-friendly value printing
 * 
 * ============================================================================
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

Value* init_value(ValueType type) {
    Value* val = malloc(sizeof(Value));
    if (!val) {
        return NULL;
    }
    val->type = type;
    switch (type) {
        case TYPE_INT:
            val->data.int_val = 0;
            break;
        case TYPE_CHAR:
            val->data.char_val = '\0';
            break;
        case TYPE_STRING:
            val->data.string_val = NULL;
            break;
    }
    return val;
}

void free_value(Value* val) {
    if (!val) {
        return;
    }
    if (val->type == TYPE_STRING && val->data.string_val) {
        free(val->data.string_val);
    }
    free(val);
}

Value* copy_value(Value* src) {
    if (!src) {
        return NULL;
    }
    Value* copy = malloc(sizeof(Value));
    if (!copy) {
        return NULL;
    }
    copy->type = src->type;
    switch (src->type) {
        case TYPE_INT:
            copy->data.int_val = src->data.int_val;
            break;
        case TYPE_CHAR:
            copy->data.char_val = src->data.char_val;
            break;
        case TYPE_STRING:
            if (src->data.string_val) {
                copy->data.string_val = strdup(src->data.string_val);
                if (!copy->data.string_val) {
                    free(copy);
                    return NULL;
                }
            } else {
                copy->data.string_val = NULL;
            }
            break;
    }
    return copy;
}

void print_value(Value* val) {
    if (!val) {
        printf("NULL");
        return;
    }
    switch (val->type) {
        case TYPE_INT:
            printf("%d", val->data.int_val);
            break;
        case TYPE_CHAR:
            printf("'%c'", val->data.char_val);
            break;
        case TYPE_STRING:
            if (val->data.string_val) {
                printf("\"%s\"", val->data.string_val);
            } else {
                printf("\"\"");
            }
            break;
    }
}
