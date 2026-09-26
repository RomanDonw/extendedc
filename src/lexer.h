#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

enum TokenType
{
    TOKEN_UNKNOWN,
    TOKEN_EOF,

    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_BACKSLASH,
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_SEMICOLON,
    TOKEN_DOT,
    TOKEN_COMMA,
    TOKEN_LT, // <
    TOKEN_GT, // >
    TOKEN_EXCL, // !
    TOKEN_AMP, // &
    TOKEN_PIPE, // |
    TOKEN_PREC, // %
    TOKEN_CIRCFLEX, // ^
    TOKEN_COLON, // :
    TOKEN_TILDE, // ~

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