#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string input_num;
int ans[500];
int main() {
	//ÖÜÆÚÎª500
	int T;
	cin >> T;
	ans[0] = 1;
	for (int i = 1; i < 500; i++)
		ans[i] = (ans[i - 1] * 2011) % 10000;
	while (T--) {
		cin >> input_num;
		int len = input_num.length();
		input_num = input_num.substr(max(0, len - 3), len);
		int num = stoi(input_num) % 500;
		cout << ans[num] << endl;
	}
	return 0;
}