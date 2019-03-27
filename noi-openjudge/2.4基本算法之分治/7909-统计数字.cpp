#include<iostream>
#include<algorithm>

using namespace std;
constexpr int MAXN = 200005;
int a[MAXN], n;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	int temp = a[1], cnt = 1;
	for (int i = 2; i <= n; i++) {
		if (a[i] == temp)cnt++;
		else {
			cout << temp << ' ' << cnt << endl;
			temp = a[i];
			cnt = 1;
		}
	}
	cout << temp << ' ' << cnt << endl;
	return 0;
}