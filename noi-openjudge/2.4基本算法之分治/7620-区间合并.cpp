#include<iostream>
#include<algorithm>

using namespace std;
constexpr int MAXN = 50005;
struct node {
	int st, ed;
}interval[MAXN];
int n;
bool compare(const node &a, const node &b) {
	if (a.st != b.st) return a.st < b.st;
	else return a.ed < b.ed;
}
int main() {
	bool no_sol = false;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> interval[i].st >> interval[i].ed;
	}
	sort(interval + 1, interval + n + 1, compare);
	int lb = interval[1].st, rb = interval[1].ed;
	for (int i = 2; i <= n; i++) {
		if (rb >= interval[i].st) {
			lb = min(lb, interval[i].st);
			rb = max(rb, interval[i].ed);
		}else {
			no_sol = true;
			break;
		}
	}
	if (no_sol)
		cout << "no" << endl;
	else
		cout << lb << ' ' << rb << endl;
	return 0;
}