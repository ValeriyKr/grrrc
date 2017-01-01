#ifndef _TOKEN_H_
#define _TOKEN_H_

enum class TokenType {
/*      TYPE            ||      MATCHES WITH     */
    Identifier,         // [a-zA-Z_][a-zA-Z0-9_]*
    Integer,            // [0-9]+
    Float,              // [0-9]+\.[0-9]*
    String,             // ".*"
    Character,          // '.'
    Semicolon,          // ;
    Lt,                 // <
    LE,                 // <=
    Gt,                 // >
    GE,                 // >=
    Eq,                 // ==
    Plus,               // +
    Minux,              // -
    Mul,                // *
    Div,                // /
    Assign,             // =
    LBracket,           // (
    RBracket,           // )
    LBrace,             // {
    RBrace,             // }
    LSBrace,            // [
    RSBrace             // ]
};


struct Token {
    explicit Token(TokenType t, size_t s, size_t e) :
        start {s},
        end {e},
        type {t}
    {
    }

    size_t start;
    size_t end;
    TokenType type;
};

#endif // _TOKEN_H_
