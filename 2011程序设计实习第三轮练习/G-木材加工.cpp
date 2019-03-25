#include<iostream>
constexpr int MAXN = 10005;
using namespace std;
int n, k, wood[MAXN];

bool feasible(int num) {
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		cnt += wood[i] / num;
	return cnt >= k;
}

int main() {
	int st = 0, ed = 0, mid;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> wood[i];
		ed += wood[i];
	}
	while (st < ed) {
		mid = (st + ed + 1) >> 1;
		if (feasible(mid)) st = mid;
		else ed = mid - 1;
	}
	cout << st << endl;
	return 0;
}