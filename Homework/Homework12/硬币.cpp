#include<cstdio>
#include<cstring>

constexpr int MAXX = 10005;
constexpr int MAXN = 205;
int dp[MAXX], n, x, a[MAXN], ans[MAXN],g[MAXX];

int main() {
	scanf("%d%d", &n, &x);
	dp[0] = 1; //dp[k] 凑到k元的方法数 选当前+不选当前
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		for (int j = x; j >= a[i]; j--)
			dp[j] += dp[j - a[i]]; //要用更新之前的更新，反向遍历
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		memset(g, 0, sizeof(g));
		// g[m] 不含第i个硬币的方案数
		for (int j = 0; j < a[i]; j++)
			g[j] = dp[j];
		for (int j = a[i]; j <= x; j++)
			g[j] = dp[j] - g[j - a[i]];
		if (g[x] == 0) ans[++cnt] = a[i];
	}
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; i++)
		printf("%d ", ans[i]);
	return 0;
}