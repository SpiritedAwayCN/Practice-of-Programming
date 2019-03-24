#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 100005;
int table[MAXN],n,m;

bool bin_search(int num, int st, int ed) {
	int mid;
	while (st <= ed) {
		mid = (st + ed) >> 1;
		if (table[mid] < num) st = mid + 1;
		else if (table[mid] == num) return true;
		else ed = mid - 1;

	}
	return false;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> table[i];
	cin >> m;
	sort(table + 1, table + n + 1);
	for (int i = 1; i <= n && table[i] <= m>>1; i++) {
		if (bin_search(m - table[i], i + 1, n)) {
			cout << table[i] << ' ' << m - table[i];
			return 0;
		}
	}
	cout << "No\n";
	return 0;
}