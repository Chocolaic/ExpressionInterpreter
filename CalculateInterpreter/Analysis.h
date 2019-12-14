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
		//��������ƥ�����ȼ�
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
	struct Pattern { regex pattern; bool isComplex = false; };//������������Ժ���
	vector<Pattern> patterns;
	map<string, Operation> operations;
	string expression;
};