#ifndef SIMPLEEXPRESSION_H
#define SIMPLEEXPRESSION_H

enum OP_TYPE { ROO, EXP, MUL, DIV, ADD, SUB, NUM_OP, NO_OP };
const char OP_CHAR[] = { '~', '^', '*', '/', '+', '-' };

#include <string>

using namespace std;

class __export SimpleExpression
{
    public:
        OP_TYPE op;
        double var_a, var_b, var_result;

        SimpleExpression();
        SimpleExpression(const string& s);
        SimpleExpression(double a, double b, OP_TYPE o);

        void   operator = (SimpleExpression& e);
        bool   operator == (SimpleExpression& e);
        double operator + (SimpleExpression& e);
        double operator - (SimpleExpression& e);
        double operator * (SimpleExpression& e);
        double operator / (SimpleExpression& e);

        double calculate();
        double calculate(const string& s);
        double calculate(double a, double b, OP_TYPE o);

    private:
        bool phrase(const string& s);

        inline double add(double a, double b);
        inline double sub(double a, double b);
        inline double mul(double a, double b);
        inline double div(double a, double b);
        inline double exp(double a, double b);
        inline double roo(double a, double b);
};

#endif
