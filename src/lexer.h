#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#if 0

enum TokenType
{
    TOKEN_UNKNOWN,
    TOKEN_EOF,

    TOKEN_KW_VOID,
    TOKEN_KW_RETURN,
    
    TOKEN_KWTYPE_INT32,
    TOKEN_KWTYPE_UINT16,

    TOKEN_EQUALS,
    TOKEN_PLUS,

    TOKEN_SEMICOLON,
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }

    TOKEN_INTEGER_LITERAL,
    TOKEN_STRING_LITERAL
} typedef TokenType;

struct Token
{
    // required fields:
    TokenType type;

    /*
    // optional fields:
    void *value; // must be equal to NULL when unused.
    size_t size;
    */
    union
    {
        //float f;
        //uint64_t integer;
        double number;
        struct { void *data; size_t size; } bytearray;
    } value;
} typedef Token;

bool lexer_next(Token *token, FILE *file); // returns 'true' on success.
void lexer_token_free(Token *token);

#endif

enum TokenType
{
    TOKEN_UNKNOWN,
    TOKEN_EOF,

    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_MINUS,

    TOKEN_LITERAL,
    TOKEN_STRING_LITERAL
} typedef TokenType;

struct Token
{
    TokenType type;
    
    void *data;
    size_t size;
} typedef Token;

bool lexer_next(FILE *file, Token *token);

#endif