#include<cstdio>
#include<algorithm>
constexpr int INF = 0x77fff0ff;
using namespace std;
int dp[1 << 16][16], dis[16][16],n;
int main() {
	//状压 dp[state][最后一个城市]
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			scanf("%d", &dis[i][j]);
		}
	for (int i = 0; i < 1 << n; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = INF;
	dp[1][0] = 0;
	int stat;
	for (int i = 3; i < (1 << n); i+=2) {
		for (int j = 0; j < n; j++) {
			if (!(i & (1 << j))) continue;
			stat = i - (1 << j);
			for (int k = 0; k < n; k++)
				if (stat & (1 << k))
					dp[i][j] = min(dp[i][j], dp[stat][k] + dis[k][j]);
		}
	}
	printf("%d", dp[(1 << n) - 1][n - 1]);
	return 0;
}