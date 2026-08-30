#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdbool.h>

enum TokenType
{
    TOKEN_UNKNOWN,
    TOKEN_EOF,

    TOKEN_KW_VOID,
    TOKEN_KW_RETURN,
    
    TOKEN_KWTYPE_INT32,
    TOKEN_KWTYPE_UINT16,

    TOKEN_OP_SET,
    TOKEN_OP_PLUS,

    TOKEN_SEMICOLON,
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }

    TOKEN_IDENTIFIER,
    TOKEN_INTEGER_LITERAL,
} typedef TokenType;

struct Token
{
    TokenType type;
    void *value; // can be unused (must be NULL if not used).
} typedef Token;

bool lexer_next(Token *token, FILE *file); // returns 'true' on success.
void lexer_token_free(Token *token);

#endif