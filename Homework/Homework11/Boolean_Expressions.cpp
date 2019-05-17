#include<iostream>
#include<string>
#include<stdexcept>
using namespace std;

bool expression_value();
bool term_and_value();
bool term_value();
bool factor_value();
char get_token() {
	char ch = cin.get();
	while (ch == ' ') ch = cin.get();
	//if (ch == EOF) exit(0);
	return ch;
}

bool expression_value() {
	bool result = term_and_value();
	bool termin = false;
	char ch;
	while (true) {
		ch = get_token();
		switch (ch)
		{
		case '|':
			result |= term_and_value();
			break;
		default:
			cin.putback(ch);
			termin = true;
			break;
		}
		if (termin) break;
	}
	return result;
}

bool term_and_value() {
	bool result = term_value();
	bool termin = false;
	char ch;
	while (true) {
		ch = get_token();
		switch (ch)
		{
		case '&':
			result &= term_value();
			break;
		default:
			cin.putback(ch);
			termin = true;
			break;
		}
		if (termin) break;
	}
	return result;
}

bool term_value() {
	bool result;
	char ch = get_token();
	if (ch == '!')
		result = !factor_value();
	else {
		cin.putback(ch);
		result = factor_value();
	}
	return result;
}
bool factor_value() {
	bool result;
	char ch = get_token();
	switch (ch){
	case '(':
		result = expression_value();
		get_token(); //读入')'
		break;
	case 'V':
		result = true;
		break;
	case 'F':
		result = false;
		break;
	case '!':
		cin.putback('!');
		result = term_value();
		break;
	default:
		throw runtime_error("Factor needed!");
		break;
	}
	return result;
}


int main() {
	int cnt = 0;
	do{
		cout << "Expression " << ++cnt << ": " << (expression_value() ? 'V' : 'F') << endl;
		//↓过滤回车
	} while (cin.get() != EOF);
	return 0;
}