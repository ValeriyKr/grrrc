#include <vector>
#include <cassert>
#include <iostream>

#include "Lexer.h"

using namespace std;

size_t tests_count;
size_t tests_success;

#define test(N, program)  \
void test##N() {          \
    tests_count++;        \
    vector<Token> except; \
    vector<Token> result = (Lexer {program}).tokens();

#define end_test(N)                                                   \
    cerr << endl << "Test " << (N) << ": ";                           \
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
    except.push_back(Token(TokenType::type, (start), (end)))

test(1, "x = 7")
    token(Identifier, 0, 1);
    token(OpAssign, 2, 3);
    token(Integer, 4, 5);
end_test(1)

test(2, "d;   a == b")
    token(Identifier, 0, 1);
    token(Semicolon, 1, 2);
    token(Identifier, 5, 6);
    token(OpEq, 7, 8);
    token(Identifier, 10, 11);
end_test(2)

int main() {
    test1();
    test2();

    cerr << endl
         << "Tests count:   " << tests_count << endl;
    cerr << "Tests success: " << tests_success << endl;

    return 0;
}
