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
};

#endif // _TOKEN_H_
