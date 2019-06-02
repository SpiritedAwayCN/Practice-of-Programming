#include<cstdio>
#include<algorithm>
using namespace std;
constexpr int MAXN = 1005;
constexpr int MAXM = 505;
constexpr int MAXK = 105;
int n, m, k, dp[MAXN][MAXM],nn[MAXK],mm[MAXK];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", &nn[i], &mm[i]);
	}

	for (int i = 1; i <= k; i++)
		for (int j = n; j >= nn[i]; j--)
			for (int k = m; k > mm[i]; k--)
				dp[j][k] = max(dp[j][k], dp[j - nn[i]][k - mm[i]] + 1);
	int ans = dp[n][m], maxhp;
	for (maxhp = m; maxhp > 0; maxhp--)
		if (dp[n][maxhp] != ans) break;
	printf("%d %d", ans, m - maxhp);
	return 0;
}