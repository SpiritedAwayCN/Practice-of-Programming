#include<iostream>
#include<algorithm>

using namespace std;
constexpr int MAXN = 100005;
int dp[MAXN],a[MAXN], n;
int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		dp[1] = a[1];
		for (int i = 2; i <= n; i++) {
			dp[i] = max(dp[i - 2] + a[i], dp[i - 1]);
			//只偷1~i的最大值
		}
		cout << dp[n] << endl;
	}

	return 0;
}