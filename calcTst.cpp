#include "calc.h"
#include <iostream>

using namespace std;

int main() {
    // Test CheckTokens with valid input
    Calc calculator1("((A+B)*(C-D))");
    Calc calculator2("(A-B)*C");
    Calc calculator3("((B*A)-G)");
    Calc calculator4("((V-R)+A)");
    Calc calculator5("(B-A)*(B*T)");
    Calc calculator6("121+12");

    if (!calculator1.CheckTokens()) {
        cout << "CheckTokens test failed\n";
    } else {
        cout << "CheckTokens test passed\n";
    }

    // Test CheckParens
    if (!calculator1.CheckParens()) {
        cout << "CheckParens test failed\n";
    } else {
        cout << "CheckParens test passed\n";
    }

    // Test Parse and DisplayInFix
    calculator1.Parse();
    calculator1.DisplayInFix();
    calculator2.Parse();
    calculator2.DisplayInFix();
    calculator3.Parse();
    calculator3.DisplayInFix();
    calculator4.Parse();
    calculator4.DisplayInFix();
    calculator5.Parse();
    calculator5.DisplayInFix();
    calculator6.Parse();
    calculator6.DisplayInFix();

    // Test InFixToPostFix and DisplayPostFix
    calculator1.InFixToPostFix();
    calculator1.DisplayPostFix();
    calculator2.InFixToPostFix();
    calculator2.DisplayPostFix();
    calculator3.InFixToPostFix();
    calculator3.DisplayPostFix();
    calculator4.InFixToPostFix();
    calculator4.DisplayPostFix();
    calculator5.InFixToPostFix();
    calculator5.DisplayPostFix();
    calculator6.InFixToPostFix();
    calculator6.DisplayPostFix();

    // Test Evaluate
    cout << "Result of evaluation: " << calculator6.Evaluate() << endl;

    return 0;
}
