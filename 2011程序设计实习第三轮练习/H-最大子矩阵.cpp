#include<iostream>
#include<cstring>
#include<algorithm>
constexpr int MAXN = 105;
using namespace std;
int n, matrix[MAXN][MAXN],max_t = 0x80000000;
int table[MAXN],dp[MAXN];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> matrix[i][j];
			//每一列是前缀和
			matrix[i][j] += matrix[i - 1][j];
		}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			for (int k = 1; k <= n; k++)
				table[k] = matrix[j][k] - matrix[i - 1][k];
			memset(dp, 0, sizeof(dp));
			for (int k = 1; k <= n; k++)
				dp[k] = max(0, dp[k - 1]) + table[k];
			for (int k = 1; k <= n; k++)
				max_t = max(max_t, dp[k]);
		}
	cout << max_t << endl;
	return 0;
}