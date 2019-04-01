#include<iostream>
#include<algorithm>

using namespace std;
constexpr int MAXN = 105;
constexpr int MAXM = 15;
int dp[MAXN][MAXM], n, m;
int main() {
	//dp[x][y] =min{ max(dp[k-1][y-1],dp[x-k][y])+1 } for k
	for (int i = 1; i <= 100; i++)
		for (int j = 1; j <= 10; j++) {
			dp[i][j] = i;
		}
	for (int i = 1; i <= 100; i++)
		for (int j = 2; j <= 10; j++)
			for (int k = 1; k < i; k++) {
				dp[i][j] = min(dp[i][j], max(dp[k - 1][j - 1], dp[i - k][j]) + 1);
			}
	while (cin >> n >> m) {
		cout << dp[n][m] << endl;
	}
	return 0;
}