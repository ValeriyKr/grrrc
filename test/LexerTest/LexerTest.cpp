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
    bool fail = false;                                 \
    cerr << endl << "Test " << (N) << ": "; 

#define end_test(N)                                                   \
    if (except.size() != result.size()) {                             \
        cerr << "Fail!" << endl;                                      \
        cerr << "\tExcepted tokens count: " << except.size() << endl; \
        cerr << "\tReceived tokens count: " << result.size() << endl; \
        cerr << "\tOnly first " << min(except.size(), result.size())  \
            << " tokens will be checked." << endl;                    \
        cerr << "--------------------------------------------------\n"; \
        fail = true;                                                  \
    }                                                                 \
    for (size_t i = 0; i < min(except.size(), result.size()); ++i)    \
        if (except[i].type != result[i].type ||                       \
            except[i].start != result[i].start ||                     \
            except[i].end != result[i].end) {                         \
            if (!fail)                                                \
                cerr << "Fail!" << endl;                              \
            cerr << "\tToken " << i << ":\n";                         \
            if (except[i].type != result[i].type)                     \
                (fail=true),cerr << "\tWrong token type" << endl;     \
            if (except[i].start != result[i].start) {                 \
                fail = true;                                          \
                cerr << "\tExcepted start position: " <<              \
                    except[i].start << endl;                          \
                cerr << "\tReceived start position: " <<              \
                    result[i].start << endl;                          \
            }                                                         \
            if (except[i].end != result[i].end) {                     \
                fail = true;                                          \
                cerr << "\tExcepted end position: " <<                \
                    except[i].end << endl;                            \
                cerr << "\tReceived end position: " <<                \
                    result[i].end << endl;                            \
            }                                                         \
        }                                                             \
    if (!fail) {                                                      \
        cerr << "Ok" << endl;                                         \
        tests_success++;                                              \
    }                                                                 \
}

#define token(type, start, end) \
    except.push_back(Token(TokenType::type, (start), (end)));

test(1, "=")
    token(Assign, 0, 1)
    token(Eof, 1, 2)
end_test(1)


test(2, "==")
    token(Eq, 0, 2)
    token(Eof, 2, 3)
end_test(2)


test(3, "5")
    token(Integer, 0, 1)
    token(Eof, 1, 2)
end_test(3)


test(4, "Simple")
    token(Identifier, 0, 6)
    token(Eof, 6, 7)
end_test(4)


test(5, "Identifie__03_5r")
    token(Identifier, 0, 16)
    token(Eof, 16, 17)
end_test(5)


test(6, "x = 7")
    token(Identifier, 0, 1)
    token(Assign, 2, 3)
    token(Integer, 4, 5)
    token(Eof, 5, 6)
end_test(6)


test(7, "d;   a == b")
    token(Identifier, 0, 1)
    token(Semicolon, 1, 2)
    token(Identifier, 5, 6)
    token(Eq, 7, 9)
    token(Identifier, 10, 11)
    token(Eof, 11, 12);
end_test(7)


test(8, "main() {\n\
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
    token(Identifier, 24, 25)
    token(Assign, 25, 26)
    token(Integer, 26, 27)
    token(Semicolon, 27, 28)
    token(Identifier, 33, 38)
    token(LBracket, 38, 39)
    token(Identifier, 39, 42)
    token(LBracket, 42, 43)
    token(Identifier, 43, 44)
    token(RBracket, 44, 45)
    token(RBracket, 45, 46)
    token(Semicolon, 46, 47)
    token(RBrace, 48, 49)
    token(Eof, 49, 50)
end_test(8)


test(9, "int main() {\n\
    float x = 0.3;\n\
    float y = 5.0;\n\
    float z=123.13;\n\
    print(i2s(y ==z));\n\
}")
    token(Identifier, 0, 3)
    token(Identifier, 4, 8)
    token(LBracket, 8, 9)
    token(RBracket, 9, 10)
    token(LBrace, 11, 12)
    token(Identifier, 17, 22)
    token(Identifier, 23, 24)
    token(Assign, 25, 26)
    token(Float, 27, 30)
    token(Semicolon, 30, 31)
    token(Identifier, 36, 41)
    token(Identifier, 42, 43)
    token(Assign, 44, 45)
    token(Float, 46, 49)
    token(Semicolon, 49, 50)
    token(Identifier, 55, 60)
    token(Identifier, 61, 62)
    token(Assign, 62, 63)
    token(Float, 63, 69)
    token(Semicolon, 69, 70)
    token(Identifier, 75, 80)
    token(LBracket, 80, 81)
    token(Identifier, 81, 84)
    token(LBracket, 84, 85)
    token(Identifier, 85, 86)
    token(Eq, 87, 89)
    token(Identifier, 89, 90)
    token(RBracket, 90, 91)
    token(RBracket, 91, 92)
    token(Semicolon, 92, 93)
    token(RBrace, 94, 95)
    token(Eof, 95, 96)
end_test(9)


test(10, R"(x="ab";y="";z="a";"")")
    token(Identifier, 0, 1)
    token(Assign, 1, 2)
    token(String, 2, 6)
    token(Semicolon, 6, 7)
    token(Identifier, 7, 8)
    token(Assign, 8, 9)
    token(String, 9, 11)
    token(Semicolon, 11, 12)
    token(Identifier, 12, 13)
    token(Assign, 13, 14)
    token(String, 14, 17)
    token(Semicolon, 17, 18)
    token(String, 18, 20)
    token(Eof, 20, 21)
end_test(10)


test(11, R"("a"[0]='c')")
    token(String, 0, 3)
    token(LSBrace, 3, 4)
    token(Integer, 4, 5)
    token(RSBrace, 5, 6)
    token(Assign, 6, 7)
    token(Character, 7, 10)
    token(Eof, 10, 11)
end_test(11)


test(12, R"("a"[0]='\c')")
    token(String, 0, 3)
    token(LSBrace, 3, 4)
    token(Integer, 4, 5)
    token(RSBrace, 5, 6)
    token(Assign, 6, 7)
    token(Character, 7, 11)
    token(Eof, 11, 12)
end_test(12)


test(13, R"("a"[0]='\\')")
    token(String, 0, 3)
    token(LSBrace, 3, 4)
    token(Integer, 4, 5)
    token(RSBrace, 5, 6)
    token(Assign, 6, 7)
    token(Character, 7, 11)
    token(Eof, 11, 12)
end_test(13)


test(14, "ifdef")
    token(Identifier, 0, 5)
    token(Eof, 5, 6)
end_test(14)


test(15, "if(a){for (x in 1..10){whilewhile; while(1) {}}}")
    token(If, 0, 2)
    token(LBracket, 2, 3)
    token(Identifier, 3, 4)
    token(RBracket, 4, 5)
    token(LBrace, 5, 6)
    token(For, 6, 9)
    token(LBracket, 10, 11)
    token(Identifier, 11, 12)
    token(In, 13, 15)
    token(Integer, 16, 17)
    token(Range, 17, 19)
    token(Integer, 19, 21)
    token(RBracket, 21, 22)
    token(LBrace, 22, 23);
    token(Identifier, 23, 33)
    token(Semicolon, 33, 34)
    token(While, 35, 40)
    token(LBracket, 40, 41)
    token(Integer, 41, 42)
    token(RBracket, 42, 43)
    token(LBrace, 44, 45)
    token(RBrace, 45, 46)
    token(RBrace, 46, 47)
    token(RBrace, 47, 48)
    token(Eof, 48, 49)
end_test(15)


int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();

    cerr << endl
         << "Tests count:   " << tests_count << endl;
    cerr << "Tests success: " << tests_success << endl;

    return 0;
}
