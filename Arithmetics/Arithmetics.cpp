#include <math.h>
#include "Arithmetics.h"

TNum::TNum(int _d)
{
    data = _d;
}

TNum::TNum(TNum& _v)
{
    this->data = _v.data;
}

TNum::TNum(char* s)
{
    int i = 0;
    while (isdigit(s[i]))
        i++;
    if (s[i] != 0)
        throw - 1;
    data = atof(s);
}

int TNum::Priority()
{
    return -1;
}

int TNum::GetNumber()
{
    return data;
}

char TNum::GetOperation()
{
    throw - 1;
}

TOperand* TNum::Calc(TOperand* a, TOperand* b)
{
    throw - 1;
}

TOperation::TOperation(char _d)
{
    data = _d;
}

TOperation::TOperation(TOperation& _v)
{
    this->data = _v.data;
}

char TOperation::GetOperation()
{
    return data;
}

int TOperation::GetNumber()
{
    throw - 1;
}

TPlus::TPlus(char _d) :TOperation(_d)
{
}

int TPlus::Priority()
{
    return 2;
}

TOperand* TPlus::Calc(TOperand* a, TOperand* b)
{
    TNum* res = new TNum(a->GetNumber() + b->GetNumber());
    return res;
}

TSub::TSub(char _d) :TOperation(_d)
{
}

int TSub::Priority()
{
    return 2;
}

TOperand* TSub::Calc(TOperand* a, TOperand* b)
{
    TNum* res = new TNum(a->GetNumber() - b->GetNumber());
    return res;
}

TMult::TMult(char _d) :TOperation(_d)
{
}

int TMult::Priority()
{
    return 3;
}

TOperand* TMult::Calc(TOperand* a, TOperand* b)
{
    TNum* res = new TNum(a->GetNumber() * b->GetNumber());
    return res;
}

TDiv::TDiv(char _d) :TOperation(_d)
{
}

int TDiv::Priority()
{
    return 3;
}

TOperand* TDiv::Calc(TOperand* a, TOperand* b)
{
    if (b->GetNumber() == 0)
        throw - 1;
    TNum* res = new TNum(a->GetNumber() / b->GetNumber());
    return res;
}

TOpenBracket::TOpenBracket(char _d) :TOperation(_d)
{
}

int TOpenBracket::Priority()
{
    return 1;
}

TOperand* TOpenBracket::Calc(TOperand* a, TOperand* b)
{
    throw - 1;
}

TEndBracket::TEndBracket(char _d) :TOperation(_d)
{
}

int TEndBracket::Priority()
{
    return 0;
}

TOperand* TEndBracket::Calc(TOperand* a, TOperand* b)
{
    throw - 1;
}

TOperand** TOperandFactory::Create(char* s, int& n)
{
    int l = strlen(s);
    n = 0;
    for (int i = 0; i < l; i++)
        if (isdigit(s[i]) == 0)
            n++;
    n++;
    n = n * 2 - 1;
    TOperand** res = new TOperand * [n];
    int start = 0;
    int j = 0;
    for (int i = 0; i < l; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            if (i == 0)
            {
                if (s[i] == '(')
                    res[j] = new TOpenBracket('(');
                else
                    throw - 1;
                j++;
                start = i + 1;
            }
            else
            {
                if (isdigit(s[i - 1]) != 0)
                {
                    char ch[256];
                    int l2 = i - start + 1;

                    for (int k = 0; k < l2 - 1; k++)
                        ch[k] = s[start + k];

                    ch[l2 - 1] = 0;
                    res[j] = new TNum(ch);
                    j++;
                }
                switch (s[i])
                {
                case '(':res[j] = new TOpenBracket('('); break;
                case ')':res[j] = new TEndBracket(')'); break;
                case '+':res[j] = new TPlus('+'); break;
                case '-':res[j] = new TSub('-'); break;
                case '*':res[j] = new TMult('*'); break;
                case '/':res[j] = new TDiv('/'); break;
                case '^':res[j] = new TPow('^'); break;
                }
                j++;
                start = i + 1;
            }
        }
    }
    char ch[256];
    int l2 = l - start + 1;
    if (l2 > 1)
    {
        for (int k = 0; k < l2 - 1; k++)
            ch[k] = s[start + k];

        ch[l2 - 1] = 0;
        res[j] = new TNum(ch);
        j++;
    }
    n = j;
    return res;
}

int TPolish::Calculate(char* s)
{
    int n = 0;
    TOperand** operands = TOperandFactory::Create(s, n);
    TOperand** res = new TOperand * [n];
    TStack<TOperand*> stack(n);
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int pri = operands[i]->Priority();
        if (pri == -1)
        {
            res[j] = operands[i];
            j++;
        }
        else
        {
            if (stack.IsEmpty() || pri == 1)
                stack.Push(operands[i]);
            else if (pri == 0)
            {
                TOperand* tmp = stack.Get();
                stack.Pop();
                while (tmp->Priority() != 1)
                {
                    res[j] = tmp;
                    j++;
                    tmp = stack.Get();
                    stack.Pop();
                }
            }
            else
            {
                TOperand* tmp = stack.Get();
                stack.Pop();
                if (pri > tmp->Priority())
                {
                    stack.Push(tmp);
                    stack.Push(operands[i]);
                }
                else
                {
                    while (pri <= tmp->Priority())
                    {
                        res[j] = tmp;
                        j++;
                        if (!stack.IsEmpty())
                        {
                            tmp = stack.Get();
                            stack.Pop();
                        }
                        else
                            break;
                    }
                    if (!stack.IsEmpty())
                        stack.Push(tmp);
                    stack.Push(operands[i]);
                }
            }
        }
    }
    while (!stack.IsEmpty())
    {
        TOperand* tmp = stack.Get();
        stack.Pop();
        res[j] = tmp;
        j++;
    }
    TStack<TOperand*> ns(n);
    for (int i = 0; i < j; i++)
    {
        if (res[i]->Priority() == -1)
            ns.Push(res[i]);
        else
        {
            TOperand* b = ns.Get();
            ns.Pop();
            TOperand* a = ns.Get();
            ns.Pop();
            TOperand* c = res[i]->Calc(a, b);
            ns.Push(c);
        }
    }
    TOperand* r = ns.Get();
    delete[] operands;
    delete[] res;
    return r->GetNumber();
}

TPow::TPow(char _d) :TOperation(_d)
{
}

int TPow::Priority()
{
    return 4;
}

TOperand* TPow::Calc(TOperand* a, TOperand* b)
{
    if (b->GetNumber() == 0)
    {
        TNum* res = new TNum(1);
        return res;
    }
    int pow = a->GetNumber();
    int sum = pow;
    for (int i = 1; i < b->GetNumber(); i++)
        sum *= pow;
    TNum* res = new TNum(sum);
    return res;
}