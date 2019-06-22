#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, p;
constexpr int MAXN = 205;
constexpr int INF = 0x3f3f3f3f;
int t[MAXN], u[MAXN], v[MAXN], x[MAXN], y[MAXN], z[MAXN];
int dp[2][50105];

int main() {
	int T, index;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &p);
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d", &t[i], &u[i], &v[i]);
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &x[i], &y[i], &z[i]);

		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = dp[1][0] = 0;
		index = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = p + 100; j > 0; j--)
				for (int k = 0; k <= v[i] && j >= k * t[i]; k++)
					dp[index][j] = min(dp[index][j], dp[index ^ 1][j - k * t[i]] + k * u[i]);
			index ^= 1;
			for (int j = p + 100; j > 0; j--)
				dp[index][j] = INF;
		}
		index ^= 1;
		int minv = INF;
		for (int j = p; j <= p + 100; j++)
			minv = min(minv, dp[index][j]);

		if (minv > 50000) {
			printf("FAIL\n");
			continue;
		}

		memset(dp, 0x3f, sizeof(dp));
		dp[0][0] = dp[1][0] = 0;
		index = 1;
		for (int i = 1; i <= m; i++) {
			for (int j = minv + 100; j > 0; j--)
				for (int k = 0; k <= z[i] && j >= k * x[i]; k++)
					dp[index][j] = min(dp[index][j], dp[index ^ 1][j - k * x[i]] + k * y[i]);
			index ^= 1;
			for (int j = minv + 100; j > 0; j--)
				dp[index][j] = INF;
		}
		index ^= 1;
		int ans = INF;
		for (int j = minv; j <= minv + 100; j++)
			ans = min(ans, dp[index][j]);
		if (ans > 50000)
			printf("FAIL\n");
		else
			printf("%d\n", ans);
	}

	return 0;
}