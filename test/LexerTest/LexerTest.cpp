#include <vector>
#include <cassert>
#include <iostream>

#include "Lexer.h"

using namespace std;

size_t tests_count;
size_t tests_success;

#define test(N, program)                               \
void test##N() {                                       \
    tests_count++;                                     \
    vector<Token> except;                              \
    vector<Token> result = (Lexer {program}).tokens(); \
    cerr << endl << "Test " << (N) << ": "; 

#define end_test(N)                                                   \
    if (except.size() != result.size()) {                             \
        cerr << "Fail!" << endl;                                      \
        cerr << "\tExcepted tokens count: " << except.size() << endl; \
        cerr << "\tReceived tokens count: " << result.size() << endl; \
        return;                                                       \
    }                                                                 \
    for (size_t i = 0; i < except.size(); ++i)                        \
        if (except[i].type != result[i].type ||                       \
            except[i].start != result[i].start ||                     \
            except[i].end != result[i].end) {                         \
            cerr << "Fail!" << endl;                                  \
            cerr << "\tToken " << i << ":\n";                         \
            if (except[i].type != result[i].type)                     \
                cerr << "\tWrong token type" << endl;                 \
            if (except[i].start != result[i].start) {                 \
                cerr << "\tExcepted start position: " <<              \
                    except[i].start << endl;                          \
                cerr << "\tReceived start position: " <<              \
                    result[i].start << endl;                          \
            }                                                         \
            if (except[i].end != result[i].end) {                     \
                cerr << "\tExcepted end position: " <<                \
                    except[i].end << endl;                            \
                cerr << "\tReceived end position: " <<                \
                    result[i].end << endl;                            \
            }                                                         \
            return;                                                   \
        }                                                             \
    cerr << "Ok" << endl;                                             \
    tests_success++;                                                  \
}

#define token(type, start, end) \
    except.push_back(Token(TokenType::type, (start), (end)));

test(1, "=")
    token(Assign, 0, 1);
end_test(1)


test(2, "==")
    token(Eq, 0, 2)
end_test(2)


test(3, "5")
    token(Integer, 0, 1)
end_test(3)


test(4, "Simple")
    token(Identifier, 0, 6)
end_test(4)


test(5, "Identifie__03_5r")
    token(Identifier, 0, 16)
end_test(5)


test(6, "x = 7")
    token(Identifier, 0, 1)
    token(Assign, 2, 3)
    token(Integer, 4, 5)
end_test(6)


test(12, "d;   a == b")
    token(Identifier, 0, 1)
    token(Semicolon, 1, 2)
    token(Identifier, 5, 6)
    token(Eq, 7, 8)
    token(Identifier, 10, 11)
end_test(12)


test(13, "main() {\n\
    int x;\n\
    x=9;\n\
    print(s2i(x));\n\
}")
    token(Identifier, 0, 4)
    token(LBracket, 4, 5)
    token(RBracket, 5, 6)
    token(LBrace, 7, 8)
    token(Identifier, 13, 16)
    token(Identifier, 17, 18)
    token(Semicolon, 18, 19)
    token(Identifier, 25, 26);
    token(Assign, 26, 27)
    token(Integer, 27, 28)
    token(Semicolon, 28, 29)
    token(Identifier, 34, 39)
    token(LBracket, 39, 40)
    token(Identifier, 40, 43)
    token(LBracket, 43, 44)
    token(Identifier, 44, 45)
    token(RBracket, 45, 46)
    token(RBracket, 46, 47)
    token(Semicolon, 47, 48)
    token(RBrace, 49, 50)
end_test(13)


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    cerr << endl
         << "Tests count:   " << tests_count << endl;
    cerr << "Tests success: " << tests_success << endl;

    return 0;
}
