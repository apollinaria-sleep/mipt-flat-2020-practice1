#include "regular_expressions.h"


int main() {
    string regexp;
    cin >> regexp;
    char letter;
    cin >> letter;
    
    Solution solve(regexp, letter);
    try {
        int answer = solve.FindSolution();
        if (answer == INF) {
            cout << "INF";
        } else {
            cout << answer;
        }
    } catch (IncorrectRegularExpression& ex) {
        cout << "ERROR";
    }

    return 0;
}
