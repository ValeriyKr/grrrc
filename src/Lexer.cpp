#include <locale>
#include <regex>

#include "Lexer.h"

using namespace std;

Lexer::Lexer(const string &source) :
    pos {0},
    src {source + '\a'}
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
    case '\a':
        return make_token(TokenType::Eof, 1);
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
        // ..
        if (pos+1 < src.length() && src.substr(pos, 2) == "..")
            return make_token(TokenType::Range, 2);
        // in / if
        if (src[pos] == 'i' && pos + 2 < src.length() && !isalnum(src[pos+2]))
            switch (src[pos+1]) {
            case 'n':
                return make_token(TokenType::In, 2);
            case 'f':
                return make_token(TokenType::If, 2);
            }
        // for
        if (pos + 3 < src.length() && !isalnum(src[pos+3])
                && src.substr(pos, 3) == "for")
            return make_token(TokenType::For, 3);
        // while
        if (pos + 5 < src.length() && !isalnum(src[pos+5])
                && src.substr(pos, 5) == "while")
            return make_token(TokenType::While, 5);
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
    regex re("^[0-9]+\\.[0-9]+[^0-9]");
    smatch match;
    const string substr = src.substr(pos);
    if (regex_search(substr, match, re) && match.size())
        return match.str(0).length()-1;
    else
        return 0;
}


size_t Lexer::get_integer() {
    size_t cpos = pos;
    for (; cpos < src.length() && isdigit(src[cpos]); ++cpos)
        ;
    return cpos - pos;
}


size_t Lexer::get_word() {
    regex re("^[a-zA-Z_][a-zA-Z0-9_]*[^a-zA-Z0-9_]");
    smatch match;
    const string substr = src.substr(pos);
    if (regex_search(substr, match, re) && match.size())
        return match.str(0).length()-1;
    else
        return 0;
}



size_t Lexer::get_string() {
    // TODO: strings with internal backslashed quotes.
    regex re(R"S(^"[^"]*")S");
    smatch match;
    const string substr = src.substr(pos);
    if (regex_search(substr, match, re) && match.size())
        return match.str(0).length();
    else
        return 0;
}


size_t Lexer::get_character() {
    regex re(R"S(^'([^\\]|(\\.))')S");
    smatch match;
    const string substr = src.substr(pos);
    if (regex_search(substr, match, re) && match.size())
        return match.str(0).length();
    else
        return 0;
    return 0;
}
