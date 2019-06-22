#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string input;
inline bool judge_reverse(int s, int t) {
	t--;
	while (s < t) {
		if (input[s] != input[t]) return false;
		s++;
		t--;
	}
	return true;
}

int main() {
	bool flag;
	int T;
	cin >> T;
	while (T--) {
		cin >> input;
		flag = false;
		for (int i = input.length(); i > 0; i--) {
			for (int j = 0; j + i <= input.length(); j++) {
				if (judge_reverse(j, j + i)) {
					flag = true;
					cout << input.substr(j, i) << endl;
					break;
				}
			}
			if (flag) break;
		}
	}

	return 0;
}