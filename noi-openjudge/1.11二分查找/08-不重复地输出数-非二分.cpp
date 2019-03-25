#include<iostream>
#include<algorithm>
constexpr int MAXN = 100005;
using namespace std;
int n, a[MAXN];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i] != a[i - 1] || i == 1)
			cout << a[i] << ' ';
	}
	return 0;
}