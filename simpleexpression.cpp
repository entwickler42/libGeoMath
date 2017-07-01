#include "simpleexpression.h"
#include <math.h>

//---------------------------------------------------------------------
SimpleExpression::SimpleExpression()
{}

//---------------------------------------------------------------------
SimpleExpression::SimpleExpression(const string& s)
{
    phrase(s);
}

//---------------------------------------------------------------------
SimpleExpression::SimpleExpression(double a, double b, OP_TYPE o)
{
    var_a = a;  var_b = b;  op = o;
}

//---------------------------------------------------------------------
void SimpleExpression::operator = (SimpleExpression& e)
{
    var_a       = e.var_a;          var_b  = e.var_b;
    var_result  = e.var_result;     op     = e.op;
}

//---------------------------------------------------------------------
bool SimpleExpression::operator == (SimpleExpression& e)
{
    return ( calculate() == e.calculate() );
}

//---------------------------------------------------------------------
double SimpleExpression::operator + (SimpleExpression& e)
{
    return calculate() + e.calculate();
}

//---------------------------------------------------------------------
double SimpleExpression::operator - (SimpleExpression& e)
{
    return calculate() - e.calculate();
}

//---------------------------------------------------------------------
double SimpleExpression::operator * (SimpleExpression& e)
{
    return calculate() * e.calculate();
}

//---------------------------------------------------------------------
double SimpleExpression::operator / (SimpleExpression& e)
{
    return calculate() / e.calculate();
}

//---------------------------------------------------------------------
double SimpleExpression::calculate()
{
    switch(op)
    {
        case ADD: var_result = add(var_a,var_b); break;
        case SUB: var_result = sub(var_a,var_b); break;
        case MUL: var_result = mul(var_a,var_b); break;
        case DIV: var_result = div(var_a,var_b); break;
        case EXP: var_result = exp(var_a,var_b); break;
        case ROO: var_result = roo(var_a,var_b); break;
    }

    return var_result;
}

//---------------------------------------------------------------------
double SimpleExpression::calculate(const string& s)
{
    phrase(s);
    return calculate();
}

//---------------------------------------------------------------------
double SimpleExpression::calculate(double a, double b, OP_TYPE o)
{
    var_a = a;  var_b = b;  op = o;
    return calculate();
}

//---------------------------------------------------------------------
bool SimpleExpression::phrase(const string& s)
{
    // We need Points...
    int pos = -1;
    if(s.find(','))
        while((pos = s.find(',')) > -1) s.replace(pos,1,".");

    unsigned int p=0;

    if(s.length() <= 0) return false;

    // Define type of Operation
    for(unsigned int i=0; i<s.length(); i++)
        for(unsigned int j=0; j<NUM_OP; j++)
            if(s[i] == OP_CHAR[j])
            {
                bool is_op = true;

                if(s[i] == '-' )
                {
                    if(i == 0)  is_op = false;
                    else        for(unsigned int k=0; k<s.length(); k++) if(s[i-1] == OP_CHAR[k]) is_op = false;

                }

                if(is_op)
                {
                    op = (OP_TYPE)j;
                    break;
                }
            }

    for(p=1; s[p] != OP_CHAR[op]; p++) {};

    var_a = atof(s.substr(0,p).c_str());
    var_b = atof(s.substr(p+1,s.length()).c_str());

    return true;
}

//---------------------------------------------------------------------
inline double SimpleExpression::add(double a, double b)
{
    return a + b;
}

//---------------------------------------------------------------------
inline double SimpleExpression::sub(double a, double b)
{
    return a - b;
}

//---------------------------------------------------------------------
inline double SimpleExpression::mul(double a, double b)
{
    return a * b;
}

//---------------------------------------------------------------------
inline double SimpleExpression::div(double a, double b)
{
    return a / b;
}

//---------------------------------------------------------------------
inline double SimpleExpression::exp(double a, double b)
{
    return pow(a,b);
}

//---------------------------------------------------------------------
inline double SimpleExpression::roo(double a, double b)
{
    return pow(a,1.0/b);
}