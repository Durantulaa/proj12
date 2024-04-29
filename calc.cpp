#include "calc.h"
#include <cctype> // Include cctype for isdigit and isalpha
#include <cstdlib> // Include cstdlib for exit function
#include <cstring>
#include <iostream>

using namespace std;

Calc::Calc(const char *argvIn) {
    stk = new Stack();
    valueTbl = new int[26];
    valueIdx = 0;
    int len = strlen(argvIn);
    inFix = new char[len + 1]; // Add 1 for the null terminator
    strcpy(inFix, argvIn);
    postFix = new char[len + 1]; // Add 1 for the null terminator
   postFix[0] = '\0'; // Initialize with null terminator
}

Calc::~Calc() {
    delete[] inFix;
    delete[] postFix; // Free the memory allocated for postFix
    delete[] valueTbl;
    delete stk;
}

bool Calc::CheckTokens() {
    for (int i = 0; inFix[i] != '\0'; i++) {
        if (!(inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '*' ||
              inFix[i] == '(' || inFix[i] == ')' ||
              ((isalpha(inFix[i]) && isupper(inFix[i]))) || isdigit(inFix[i]))) {
            cout << "Invalid Input\n";
            return false;
        }
    }
    return true;
}

void Calc::MakeValueTbl() {
    for (int i = 0; i < 26; i++)
        valueTbl[i] = 0;
}

int Calc::FindLast(int cur) {
    int last = cur;
    while (isdigit(inFix[last++])) {
        if (!isdigit(inFix[last]))
            return last;
    }
    return last; // return last digit
}

void Calc::Parse() {
    MakeValueTbl(); // initialize value table
    int len = strlen(inFix);
    int i = 0; // initialize loop index
    while (i < len) {
        if (isalpha(inFix[i])) {
            // find the last index of the variable
            int lastIndex = FindLast(i);
            // convert variable to index in value table
            int varIndex = inFix[i] - 'A';
            // if variable hasn't been assigned a value, set it to zero
            if (valueTbl[varIndex] == 0) {
                valueTbl[varIndex] = 0;
            }
            // move to the next character after the variable
            i = lastIndex;
        } else {
            // move to the next character
            i++;
        }
    }
}

bool Calc::CheckParens() {
    bool bal = true; // idk what exactly this does
    int i = 0;
    char ch = inFix[i];
    while (bal && ch != '\0') {
        if (ch == '(')
            stk->Push(ch);
        else if (ch == ')') {
            if (stk->IsEmpty())
                return false;
            stk->Pop();
        }
        i++;
        ch = inFix[i];
    }
    if (bal && stk->IsEmpty())
        return true;
    return false;
}

void Calc::DisplayInFix() { cout << "InFix: " << inFix << endl; }

void Calc::InFixToPostFix() {
    char ch;
    int i = 0; // Add an index variable
    for (int j = 0; inFix[j] != '\0'; j++) {
        ch = inFix[j];
        if (isdigit(ch) || isalpha(ch)) {
            postFix[i++] = ch; // Use indexing to access elements
        } else if (ch == '(') {
            stk->Push(ch);
        } else if (ch == '+' || ch == '-' || ch == '*') {
            stk->Push(ch);
        } else if (ch == ')') {
            while (!stk->IsEmpty() && stk->Peek() != '(') {
                postFix[i++] = stk->Peek(); // Use indexing to access elements
                stk->Pop();
            }
            stk->Pop(); // Pop '('
        }
    }
    postFix[i] = '\0'; // Add null terminator at the end
}

void Calc::DisplayPostFix() { cout << "PostFix: " << postFix << endl; }

int Calc::Evaluate() {
    char ch;
    int op1, op2;
    for (int i = 0; inFix[i] != '\0'; i++) {
        ch = inFix[i];
        if (isalpha(ch)) {
            stk->Push(valueTbl[ch - 'A']); // Push the value of the variable onto the stack
        } else if (isdigit(ch)) {
            stk->Push(ch - '0'); // Push the digit onto the stack
        } else if (ch == '+' || ch == '-' || ch == '*') {
            op2 = stk->Pop();
            op1 = stk->Pop();
            switch (ch) {
                case '+':
                    stk->Push(op1 + op2);
                    break;
                case '-':
                    stk->Push(op1 - op2);
                    break;
                case '*':
                    stk->Push(op1 * op2);
                    break;
            }
        }
    }
    return stk->Pop(); // Return the final result
  }
