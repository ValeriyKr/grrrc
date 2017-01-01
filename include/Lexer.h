#ifndef _LEXER_H_
#define _LEXER_H_

#include <string>
#include <vector>
#include <memory>

#include "Token.h"

class Lexer {
public:
    explicit Lexer(const std::string &source);
    std::vector<Token> tokens();

private:
    size_t pos;
    std::string src;
    std::vector<Token> _tokens;

    std::unique_ptr<Token> next();
    std::unique_ptr<Token> make_token(TokenType type, size_t size);
    size_t get_float();
    size_t get_integer();
    size_t get_string();
    size_t get_character();
    size_t get_word();
};

#endif // _TOKEN_H_
