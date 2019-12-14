#pragma once
#include "Interpreter.h"

#include <vector>
#include <map>
#include <string>
#include <regex>

typedef double (*Operation)(double, double);

using namespace std;

class Expression {
public:
	Expression(string e):expression("("+e+")") {
		//设置运算匹配优先级
		patterns.push_back(Pattern{ regex("([\\d\\.]+)([\\^])([\\d\\.]+)"), false });
		patterns.push_back(Pattern{ regex("([\\d\\.]+)([\\*/%])([\\d\\.]+)"), false });
		patterns.push_back(Pattern{ regex("([\\d\\.]+)([\\+\\-])([\\d\\.]+)"), false });
		operations["^"] = pow;
		operations["*"] = mul;
		operations["/"] = div;
		operations["%"] = mod;
		operations["+"] = add;
		operations["-"] = sub;
		matchNode(expression);
	}
	string calculate(string exp);
	double formatValue();
private:
	void matchNode(string s);
	struct Pattern { regex pattern; bool isComplex = false; };//复合运算符，以后考虑
	vector<Pattern> patterns;
	map<string, Operation> operations;
	string expression;
};