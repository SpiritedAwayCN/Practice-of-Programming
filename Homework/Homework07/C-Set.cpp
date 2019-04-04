#include<iostream>
#include<string>
#include<set>

using namespace std;
multiset<int> Container;
set<int> vis;

int main() {
	int n, arg;
	string command;
	cin >> n;
	while (n--) {
		cin >> command >> arg;
		if (command == "add") {
			Container.insert(arg);
			vis.insert(arg);
			cout << Container.count(arg) << endl;
		}
		else if (command == "ask") {
			int num = Container.count(arg);
			cout << (vis.find(arg)!=vis.end() ? 1 : 0)<<' ' << num << endl;
		}
		else {
			cout << Container.count(arg) << endl;
			Container.erase(arg);
		}
	}
	return 0;
}