#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include "simpleexpression.h"

using namespace std;

class __export Expression
{
    public:
        double var_result;

        Expression();
        Expression(const string& s);

        double calculate (const string& s);

    private:
        vector<double> vValue;
        vector<OP_TYPE> vOperator;

        bool calculate(string& s, OP_TYPE op);
        bool solveBrackets(string& s);
        bool phrase(string s);
};

#endif
