#include "expression.h"
#include <stdio.h>

//---------------------------------------------------------------------
Expression::Expression()
{}

//---------------------------------------------------------------------
Expression::Expression(const string& s)
{
    calculate(s);
}

//---------------------------------------------------------------------
double Expression::calculate (const string& s)
{
    string buf(s);

    for(unsigned int i=0; i<NUM_OP; i++)
        if(!calculate(buf,(OP_TYPE)i)) break;

    return var_result;
}

//---------------------------------------------------------------------
bool Expression::calculate(string& s, OP_TYPE op)
{
    if(!solveBrackets(s))   return false;
    if(!phrase(s))          return false;

    // return if we just have one operator & some error checking ...
    if(vOperator.size() == 1) // Simple Expression ...
    {
        var_result = SimpleExpression(s).calculate();
        return false;
    }
    else if(vOperator.size() < 1)   {   return false; } // No Operator
    if(vValue.size() < 2)           {   return false; } // No Values

    // phrase the string ...
    char buf[1024]; s.clear();
    memset(buf,'\0',1024);

    for(unsigned int pos_op=0; pos_op < vOperator.size(); pos_op++)
    {
        if(vOperator[pos_op] == op)
        {
            var_result = SimpleExpression(vValue[pos_op],vValue[pos_op+1],op).calculate();

            if(pos_op < vOperator.size() -1 )   sprintf(buf,"%f%c", var_result, OP_CHAR[vOperator[++pos_op]]);
            else                                sprintf(buf,"%f",var_result);

            s.append(buf);
        }
        else
        {
            sprintf(buf,"%f%c", vValue[pos_op], OP_CHAR[vOperator[pos_op]]);
            s.append(buf);
        }
    }

    sprintf(buf,"%f", vValue[vOperator.size()]);
    s.append(buf);

    // rekursion wenn weitere rechenoperatoren vom typ op
    if(s.find(OP_CHAR[op],0)!=-1) calculate(s,op);

    //Garbage Collection
    return true;
}

//---------------------------------------------------------------------
bool Expression::solveBrackets(string& s)
{
    unsigned int c_open = 0, c_close = 0;
    char buf[256];
    
    // Klammern zählen...
    for(unsigned int i=0; i<s.length(); i++)
        switch(s[i])
        {
            case '(': c_open++;  break;
            case ')': c_close++; break;
        };

    // Fehlerkorrektur
    if( c_open == 0 && c_close == 0 ) return true;  // no ( more ) brackets
    if( c_open != c_close )           return false; // error in expression

    // Innerste Klammer ausgehend von links extrahieren
    unsigned int s_pos = 0, e_pos = 0, c = 0;

    for(unsigned int i=0; i<s.length(); i++)
    {
        if( s[i] == '(' ) c++;
        if( c == c_open ) { s_pos = i+1; break; }
    }
    for(unsigned int i=s_pos; i<s.length(); i++) if( s[i] == ')' )  { e_pos = i;  break; }

    string s_left  = s.substr(0,s_pos-1);
    string s_right = s.substr(e_pos+1,s.length());

    // Innerste Klammer berechnen & Ergebniss ohne Klammern wieder zurück in den string schreiben
    sprintf(buf,"%f",calculate(s.substr(s_pos,(e_pos-s_pos))));
    s = s_left + string(buf) + s_right;

    // ggf rekursiver aufruf an solveBrackets um weitere klammern zu auf zu lösen
    return solveBrackets(s);
}

//---------------------------------------------------------------------
bool Expression::phrase(string s)
{
    // clear the storages
    vOperator.clear();  vValue.clear();

    // count Expressions and save operators
    for(unsigned int i=0; i<s.length(); i++)
        for(unsigned int j=0; j<NUM_OP; j++)
            if( s[i] == OP_CHAR[j] )
            {
                // negative zahlen erkennen
                bool is_op = true;

                if( s[i] == '-' )
                {
                    if      (i      ==  0 ) is_op = false;
                    else if (s[i-1] == '|') is_op = false;
                }

                if(is_op)
                {
                    vOperator.push_back(OP_TYPE(j));
                    s[i] = '|';
                }
            }

    if(vOperator.size() == 0)
    {
        var_result = atof(s.c_str());
        return false;
    }

    // get values and save them
    char *chp;

    if((chp = strtok(s.begin(),"|")) != NULL)
    {
        vValue.push_back(atof(chp));
        while((chp = strtok(NULL,"|"))!=NULL) vValue.push_back(atof(chp));
    }

    return true;
}

