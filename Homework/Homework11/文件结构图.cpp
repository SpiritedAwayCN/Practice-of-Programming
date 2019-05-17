#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
string temp;
bool termin = false;
void list_dir(int depth) {
	if (termin) return;
	vector<string> file_list;
	while (cin >> temp) {
		if (temp[0] == ']') break;
		if (temp[0] == '*') {termin = true; break;}
		
		if (temp[0] == 'f') {
			file_list.push_back(temp);
		}
		else {
			for (int i = 0; i < depth+1; i++) cout << "|     ";
			cout << temp << endl;
			list_dir(depth + 1);
		}	
	}
	sort(file_list.begin(), file_list.end());
	for_each(file_list.begin(), file_list.end(), [depth](const string& x) {
		for (int i = 0; i < depth; i++) cout << "|     ";
		cout << x << endl;
	});
}

int main() {
	freopen("in.txt", "r", stdin);
	int cnt = 0;
	char ch;
	while (true) {
		cin >> ch;
		termin = false;
		if (ch == '#') break;
		cin.putback(ch);
		cout <<"DATA SET "<<++cnt << ":\n"<< "ROOT" << endl;
		list_dir(0);
		putchar('\n');
	}
	return 0;
}