#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 205;
constexpr int INF = 0x7fffffff;
int dp[MAXN][MAXN], a[MAXN], n;

int get_dp(int s, int t) {
	if (dp[s][t] != -1) return dp[s][t];
	int temp = INF;
	for (int i = s; i < t; i++)
		temp = min(temp, get_dp(s, i) + get_dp(i + 1, t));
	if (a[s] == a[t])
		temp = min(temp, get_dp(s, t - 1));
	return dp[s][t] = temp;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cntT = 1; cntT <= T; cntT++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= n; i++)
			dp[i][i] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < i; j++)
				dp[i][j] = 0;
		printf("Case %d: %d\n", cntT, get_dp(1, n));
	}
	return 0;
}