#include "regular_expressions.h"


Solution::Solution(const string &regular_expression, const char &letter) {
    polish_notation_ = regular_expression;
    letter_ = letter;
}


int Solution::FindSolution() {
    for (const char symbol : polish_notation_) {
        if (symbol == letter_a || symbol == letter_b || symbol == letter_c || symbol == letter_1) {
            regular_expressions_.push(AddSymbol(symbol));
        } else if (symbol == operation_union) {
            regular_expressions_.push(Union());
        } else if (symbol == operation_multi) {
            regular_expressions_.push(Multi());
        } else if (symbol == operation_star) {
            regular_expressions_.push(Star());
        } else {
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
    } else if (symbol == letter_1) {
        new_expr.max_word = 0;
    }
    return new_expr;
}


RegularExpression Solution::Union() {
    if (regular_expressions_.size() < 2) {
        throw IncorrectRegularExpression();
    }
    RegularExpression right = regular_expressions_.top();
    regular_expressions_.pop();
    RegularExpression left = regular_expressions_.top();
    regular_expressions_.pop();
    RegularExpression union_{max(left.max_prefix, right.max_prefix), max(left.max_word, right.max_word)};
    return union_;
}


RegularExpression Solution::Multi() {
    if (regular_expressions_.size() < 2) {
        throw IncorrectRegularExpression();
    }
    RegularExpression right = regular_expressions_.top();
    regular_expressions_.pop();
    RegularExpression left = regular_expressions_.top();
    regular_expressions_.pop();
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
    if (expr.max_word == -1 || !expr.max_word) {
        star_.max_prefix = expr.max_prefix;
        star_.max_word = 0;
    } else {
        star_.max_prefix = star_.max_word = INF;
    }
    return star_;
}
