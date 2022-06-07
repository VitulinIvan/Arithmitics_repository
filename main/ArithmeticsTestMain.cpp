#include <iostream>
#include "Stack.h"
#include "Arithmetics.h"

int main()
{
	TPolish ans;
	char* s = new char[256];
	cin >> s;
	cout << ans.Calculate(s);
	return 0;
}