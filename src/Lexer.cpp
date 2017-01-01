#include <locale>

#include "Lexer.h"

using namespace std;

Lexer::Lexer(const string &source) :
    pos {0},
    src {source}
{
}


vector<Token> Lexer::tokens() {
    for (auto t = next(); t != nullptr; t = next())
        _tokens.push_back(*t);

    return _tokens;
}


unique_ptr<Token> Lexer::next() {
    if (pos >= src.length()) return nullptr;

    for (; pos < src.length() && isspace(src[pos]); ++pos);
    if (pos >= src.length()) return nullptr;

    pos++;
    return make_unique<Token>(TokenType::Eq, pos-1, pos);

    return nullptr;
}

