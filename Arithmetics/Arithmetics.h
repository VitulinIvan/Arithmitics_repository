#pragma once

#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include "Stack.h"

class TOperand
{
protected:

public:
	virtual int Priority() = 0;
	virtual int GetNumber() = 0;
	virtual char GetOperation() = 0;
	virtual TOperand* Calc(TOperand* a, TOperand* b) = 0;
};

class TNum : public TOperand
{
protected:
	int data;
public:
	TNum(int _d);
	TNum(TNum& _v);
	TNum(char* s);
	virtual int Priority();
	virtual int GetNumber();
	virtual char GetOperation();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TOperation : public TOperand
{
protected:
	char data;
public:
	TOperation(char _d);
	TOperation(TOperation& _v);
	virtual int GetNumber();
	virtual char GetOperation();
};

class TPlus : public TOperation
{
protected:

public:
	TPlus(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TSub : public TOperation
{
protected:

public:
	TSub(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TMult : public TOperation
{
protected:

public:
	TMult(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TDiv : public TOperation
{
protected:

public:
	TDiv(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TOpenBracket : public TOperation
{
protected:

public:
	TOpenBracket(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TEndBracket : public TOperation
{
protected:

public:

	TEndBracket(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};

class TOperandFactory
{
public:
	static TOperand** Create(char* s, int& n);
};

class TPolish
{
public:
	static int Calculate(char* s);
};

class TPow : public TOperation
{
protected:

public:
	TPow(char _d);
	virtual int Priority();
	virtual TOperand* Calc(TOperand* a, TOperand* b);
};