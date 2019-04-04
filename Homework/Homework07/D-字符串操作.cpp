#include<iostream>
#include<string>
using namespace std;
string table[21];

inline string do_copy();
inline string do_add();
inline int do_find();
inline int do_rfind();

string get_string() {
	string command;
	cin >> command;
	if (command == "copy") {
		return do_copy();
	}
	else if (command == "add") {
		return do_add();
	}
	else {
		return command;
	}
}
int get_n() {
	string command;
	cin >> command;
	if (command == "find") {
		return do_find();
	}
	else if (command == "rfind") {
		return do_rfind();
	}
	else {
		return stoi(command);
	}
}

string do_copy() {
	int N = get_n();
	int X = get_n();
	int L = get_n();
	return table[N].substr(X, L);
}

inline bool judge_num(const string& str) {
	if (str.length() > 5) return false;
	for (int i = 0; i < str.length(); i++)
		if (!isdigit(str[i])) return false;
	return true;
}
string do_add() {
	string S1 = get_string();
	string S2 = get_string();
	if (judge_num(S1) && judge_num(S2)) {
		int ans = stoi(S1) + stoi(S2);
		return to_string(ans);
	}
	return S1 + S2;
}
int do_find() {
	string S = get_string();
	int N = get_n();
	return table[N].find(S);
}
int do_rfind() {
	string S = get_string();
	int N = get_n();
	return table[N].rfind(S);
	
}
inline void do_insert() {
	string S = get_string();
	int N = get_n();
	int X = get_n();
	table[N].insert(X, S);
}
inline void do_reset() {
	string S = get_string();
	int N = get_n();
	table[N] = S;
}
inline void do_print() {
	int N = get_n();
	cout << table[N] << endl;
}
inline void do_printall(int n) {
	for (int i = 1; i <= n; i++) {
		cout << table[i] << endl;
	}
}

int main() {
	int n;
	string command;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> table[i];
	do {
		cin >> command;
		if (command == "over") break;
		if (command == "insert") {
			do_insert();
		}
		else if (command == "reset") {
			do_reset();
		}
		else if (command == "print") {
			do_print();
		}
		else if (command == "printall") {
			do_printall(n);
		}
	} while (true);

	return 0;
}