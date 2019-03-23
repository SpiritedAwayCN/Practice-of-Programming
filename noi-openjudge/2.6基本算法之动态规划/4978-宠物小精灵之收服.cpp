#include<iostream>

constexpr int MAXN = 1005;
constexpr int MAXM = 505;
constexpr int MAXK = 105;
using namespace std;

short dp[MAXN][MAXM];
//二维背包问题 前i个物品，j个球，k点生命能补到的个数（降维）
//最后找满足个数最大的最小生命值
int n, m, K, ball[MAXK], hp[MAXK];
int main() {
	cin >> n >> m >>K;
	for (int i = 1; i <= K; i++)
		cin >> ball[i] >> hp[i];
	for (int i = 1; i <= K; i++)
		for (int j = n; j >= ball[i]; j--)
			for (int k = m; k > hp[i]; k--) {
				if(dp[j - ball[i]][k - hp[i]] + 1>dp[j][k])
					dp[j][k] = dp[j - ball[i]][k - hp[i]] + 1;
			}
	int ans = dp[n][m], k = m - 1;
	while (dp[n][k] == ans && k > 0)k--;
	//注：上面可以二分
	cout << ans << ' ' << m - k << endl;
	return 0;
}
