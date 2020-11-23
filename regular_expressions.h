#ifndef FORMAL_SOLVER_H
#define FORMAL_SOLVER_H
#include <iostream>
#include <stack>
#include <string>
#include <exception>
#include <limits>


using namespace std;


const int INF = numeric_limits<int>::max();


enum Symbols {
    LetterA = 97,
    LetterB = 98,
    LetterC = 99,
    Epsilon = 49,
    OperationUnion = 43,
    OperationMulti = 46,
    OperationStar = 42
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
    stack <RegularExpression> regular_expressions_;
    string polish_notation_;
    char letter_;
    RegularExpression AddSymbol(const char& symbol) const;
    RegularExpression Union();
    RegularExpression Multi();
    RegularExpression Star();
    pair<RegularExpression, RegularExpression> GetTopTwoElements();
};


#endif
