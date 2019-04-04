#include<iostream>
#include<string>
#include<list>

using namespace std;
list<int> sequence[10000];

int main() {
	int n, tot = 0;
	int arg1, arg2;
	string command;
	cin >> n;
	while (n--) {
		cin >> command;
		switch (command[0]){
		case 'n':
			cin >> arg1;
			break;
		case 'a':
			cin >> arg1 >> arg2;
			sequence[arg1].push_back(arg2);
			break;
		case 'o': {
			cin >> arg1;
			sequence[arg1].sort();
			for (int i : sequence[arg1]) {
				cout << i << ' ';
			}
			cout << endl;
			break;
		}
		case 'm':
			cin >> arg1 >> arg2;
			sequence[arg1].merge(sequence[arg2]);
			break;
		case 'u':
			cin >> arg1;
			sequence[arg1].sort();
			sequence[arg1].unique();
			break;
		}
	}
	return 0;
}