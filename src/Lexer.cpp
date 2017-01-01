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

    switch (src[pos]) {
    case ';':
        return make_token(TokenType::Semicolon, 1);
    case '-':
        return make_token(TokenType::Minus, 1);
    case '+':
        return make_token(TokenType::Plus, 1);
    case '/':
        return make_token(TokenType::Div, 1);
    case '(':
        return make_token(TokenType::LBracket, 1);
    case ')':
        return make_token(TokenType::RBracket, 1);
    case '{':
        return make_token(TokenType::LBrace, 1);
    case '}':
        return make_token(TokenType::RBrace, 1);
    case '[':
        return make_token(TokenType::LSBrace, 1);
    case ']':
        return make_token(TokenType::RSBrace, 1);
    case '<':
        return (pos + 1 != src.length() && src[pos+1] == '=') ?
            make_token(TokenType::LE, 2) :
            make_token(TokenType::Lt, 1);
    case '>':
        return (pos + 1 != src.length() && src[pos+1] == '=') ?
            make_token(TokenType::GE, 2) :
            make_token(TokenType::Gt, 1);
    case '=':
        return (pos + 1 != src.length() && src[pos+1] == '=') ?
            make_token(TokenType::Eq, 2) :
            make_token(TokenType::Assign, 1);
    case '*':
        return (pos + 1 != src.length() && src[pos+1] == '*') ?
            make_token(TokenType::Power, 2) :
            make_token(TokenType::Mul, 1);
    default:
        size_t len = get_float();
        if (len > 1)
            return make_token(TokenType::Float, len);
        len = get_integer();
        if (len > 0)
            return make_token(TokenType::Integer, len);
        len = get_string();
        if (len > 1)
            return make_token(TokenType::String, len);
        len = get_character();
        if (len > 2)
            return make_token(TokenType::Character, len);
        len = get_word();
        if (len > 0)
            return make_token(TokenType::Identifier, len);
    }

    return nullptr;
}


unique_ptr<Token> Lexer::make_token(TokenType type, size_t size) {
    unique_ptr<Token> t = make_unique<Token>(type, pos, pos+size);
    pos += size;
    return t;
}


size_t Lexer::get_float() {
    if (!isdigit(src[pos])) return 0;
    bool found_dot = false;
    size_t cpos = pos;
    for (; cpos < src.length(); ++cpos) {
        char c = src[cpos];
        if (!isdigit(c)) {
            if ('.' == c) {
                if (!found_dot) {
                    found_dot = true;
                    continue;
                }
                return 0;
            } else if ((c == ';' || isspace(c)) && found_dot) {
                return cpos - pos;
            } else {
                return 0;
            }
        }
    }
    return found_dot ? cpos - pos : 0;
}


size_t Lexer::get_integer() {
    size_t cpos = pos;
    for (; cpos < src.length() && isdigit(src[cpos]); ++cpos)
        ;
    return cpos - pos;
}


size_t Lexer::get_word() {
    if (!isalpha(src[pos]) || src[pos] != '_') return 0;
    size_t cpos = pos;
    for (; cpos < src.length(); ++cpos)
        if (!(isalnum(src[cpos]) || src[cpos] == '_'))
            return cpos - pos;
    return cpos - pos;
}



size_t Lexer::get_string() {
    if (src[pos] != '"') return 0;
    size_t cpos = pos + 1;
    for (; cpos < src.length()
            && src[cpos] != '"' && src[cpos-1] != '\\'; ++cpos)
        ;
    if (cpos >= src.length() || src[cpos] != '"') return 0;
    return cpos - pos;
}


size_t Lexer::get_character() {
    if (src[pos] == '\'') {
        if (pos+1 < src.length() && src[pos+1] == '\\') {
            if (pos+3 < src.length() && src[pos+3] == '\'')
                return 4;
        } else if (pos+2 < src.length() && src[pos+2] == '\'') {
            return 3;
        }
    }
    return 0;
}
