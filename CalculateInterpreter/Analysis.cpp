#include "Analysis.h"

#include <iostream>
#include <vector>

void replaceStr(string& baseStr, string oldStr, string newStr) {
	baseStr.replace(baseStr.find(oldStr), oldStr.size(), newStr);
}


void Expression::matchNode(string s)//由childNode向parentNode匹配
{
	smatch results;
	if (regex_search(s, results, regex("\\(([^\\(\\)]+)\\)"))) {
		if (results.size() > 1)
			replaceStr(expression, results[0], calculate(results[1]));//消除childNode 树高度-1
		cout << "->" << expression << endl;
		return matchNode(expression);
	}
	
}

string Expression::calculate(string exp)//计算表达式
{
	
	for (auto i = patterns.begin(); i != patterns.end(); i++) {
		smatch results;
		if (regex_search(exp, results, i->pattern)) {
			double a = atof(results[1].str().c_str()),
				b = atof(results[3].str().c_str()),
				r = operations[results[2].str()](a, b);
			replaceStr(exp, results[0].str(), to_string(r));
			return calculate(exp);
		}
	}
	return exp.c_str();
}

double Expression::formatValue() {
	return atof(expression.c_str());
}

