// реализация пользовательского приложения

#include "arithmetic.h"

int main()
{
    try
   {
        Arithmetic f;
        cout << "Write your expression:" << endl;
        string str;
        getline(cin, str);
        cout << "Expression is after translting to string: " << endl;
        f.translateStrToTerm(str);
         f.PrintVecT();
         cout << "Polish Note: " << endl;
        f.TermToPolishNote();
        f.PrintVectP();
        cout << "Result expression: " << endl;
        f.calculate();
    }
    catch (char* error) 
    {
        cout << error << endl;
    }
}
