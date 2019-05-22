#include<cstdio>

constexpr int MAXN = 255;
long long n, dp[MAXN][MAXN], ans[MAXN];

int main() {
	for (int i = 1; i <= 250; i++) {
		dp[i][i] = 1;
		if ((i & 1) == 0) dp[i][i >> 1] = 1;
	}
		
	//dp[i][k] 长度为i，第一与最后一项为k的总数
	for (int i = 1; i <= 250; i++)
		for (int j = 1; j < (i+1) >> 1; j++) {
			for (int k = j; k <= i - 2 * j; k++)
				dp[i][j] += dp[i - 2 * j][k];
		}

	for (int i = 1; i <= 250; i++)
		for (int j = 1; j <= i; j++)
			ans[i] += dp[i][j];
	while (true) {
		scanf("%lld", &n);
		if (n == 0)break;
		printf("%lld %lld\n", n, ans[n]);
	}
	return 0;
}