#include<cstdio>
#include<stack>
#include<queue>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n;
priority_queue<double, vector<double>, greater<double>> number_list;
stack<double> calc;
int main() {
	scanf("%d", &n);
	double temp;
	char str[20];
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &temp);
		number_list.push(temp);
	}
	while (scanf("%s", str) == 1) {
		if((str[0] == '+'&&strlen(str) == 1) || (str[0] == '-'&&strlen(str)==1) || str[0] == '*' || str[0] == '/' || str[0] == '^'){
			double num2 = calc.top();
			calc.pop();
			double num1 = calc.top();
			calc.pop();
			switch (str[0])
			{
			case '+':
				calc.push(num1 + num2);
				break;
			case '-':
				calc.push(num1 - num2);
				break;
			case '*':
				calc.push(num1 * num2);
				break;
			case '/':
				calc.push(num1 / num2);
				break;
			case '^':
				calc.push(pow(num1, num2));
				break;
			}
		}else if (str[0] == '=') {
			double num = calc.top();
			printf("%e\n", num);
			number_list.pop();
			number_list.push(num);
			while (!calc.empty())  calc.pop();
		} else{
			calc.push(atof(str));
		}
	}
	int n = 0;
	putchar('\n');
	while (!number_list.empty()) {
		n++;
		printf("%e ", number_list.top());
		number_list.pop();
		if (n % 10 == 0)
			putchar('\n');
	}
	return 0;
}