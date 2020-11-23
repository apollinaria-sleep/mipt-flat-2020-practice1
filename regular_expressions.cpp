#include "regular_expressions.h"


Solution::Solution(const string &regular_expression, const char &letter) {
    polish_notation_ = regular_expression;
    letter_ = letter;
}


int Solution::FindSolution() {
    for (const char symbol : polish_notation_) {
        switch (symbol) {
            case LetterA:
            case LetterB:
            case LetterC:
            case Epsilon:
                regular_expressions_.push(AddSymbol(symbol));
                break;
            case OperationUnion:
                regular_expressions_.push(Union());
                break;
            case OperationMulti:
                regular_expressions_.push(Multi());
                break;
            case OperationStar:
                regular_expressions_.push(Star());
                break;
            default:
                throw IncorrectRegularExpression();
        }
    }
    if (regular_expressions_.size() != 1) {
        throw IncorrectRegularExpression();
    }
    return regular_expressions_.top().max_prefix;
}


RegularExpression Solution::AddSymbol(const char &symbol) const{
    RegularExpression new_expr;
    if (symbol == letter_) {
        new_expr.max_prefix = 1;
        new_expr.max_word = 1;
    } else if (symbol == Epsilon) {
        new_expr.max_word = 0;
    }
    return new_expr;
}


pair<RegularExpression, RegularExpression> Solution::GetTopTwoElements() {
    if (regular_expressions_.size() < 2) {
        throw IncorrectRegularExpression();
    }
    RegularExpression right = regular_expressions_.top();
    regular_expressions_.pop();
    RegularExpression left = regular_expressions_.top();
    regular_expressions_.pop();
    return make_pair(left, right);
}


RegularExpression Solution::Union() {
    auto [left, right] = GetTopTwoElements();
    RegularExpression union_{max(left.max_prefix, right.max_prefix), max(left.max_word, right.max_word)};
    return union_;
}


RegularExpression Solution::Multi() {
    auto [left, right] = GetTopTwoElements();
    RegularExpression multi_;
    multi_.max_prefix = max(left.max_prefix, (left.max_word != -1 ? left.max_word + right.max_prefix : -1));
    if (left.max_word == -1 || right.max_word == -1) {
        multi_.max_word = -1;
    } else {
        multi_.max_word = left.max_word + right.max_word;
    }
    return multi_;
}


RegularExpression Solution::Star() {
    if (regular_expressions_.empty()) {
        throw IncorrectRegularExpression();
    }
    RegularExpression expr = regular_expressions_.top();
    regular_expressions_.pop();
    RegularExpression star_;
    if (expr.max_word == -1 || expr.max_word == 0) {
        star_.max_prefix = expr.max_prefix;
        star_.max_word = 0;
    } else {
        star_.max_prefix = star_.max_word = INF;
    }
    return star_;
}
