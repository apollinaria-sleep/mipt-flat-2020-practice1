#ifndef FORMAL_SOLVER_H
#define FORMAL_SOLVER_H
#include <iostream>
#include <stack>
#include <string>
#include <exception>
#include <limits>


using namespace std;


enum Symbols {
    letter_a = 97,
    letter_b = 98,
    letter_c = 99,
    letter_1 = 49,
    operation_union = 43,
    operation_multi = 46,
    operation_star = 42
};


class IncorrectRegularExpression : public exception {
    const char* what() const noexcept override {
        return "Incorrect regular expression";
    }
};


struct RegularExpression {
    int max_prefix = 0;    //максимальное k, такое что в RegularExpression есть слова, начинающиеся с x^k.
    int max_word = -1;     //максимальное n, такое что в RegularExpression есть слово x^n.
};


class Solution {
public:
    Solution(const string& regular_expression, const char& letter);
    int FindSolution();
private:
    const int INF = numeric_limits<int>::max();
    stack <RegularExpression> regular_expressions_;
    string polish_notation_;
    char letter_;
    RegularExpression AddSymbol(const char& symbol) const;
    RegularExpression Union();
    RegularExpression Multi();
    RegularExpression Star();
};


#endif
