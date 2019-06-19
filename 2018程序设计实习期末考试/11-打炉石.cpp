#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

constexpr int MAXN = 1005;
constexpr int INF = 0x7f7f7f7f;
int dp[2][MAXN][11], n, m, k, h;
int a[MAXN], b[MAXN], c[MAXN];

inline void update_min(int& dist, int key) {
	dist = min(dist, key);
	if (dist > h) dist = INF;
}

int main() {
	scanf("%d%d%d%d", &n, &k, &m, &h);
	memset(dp, 0x7f, sizeof(dp));
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
	int index = 0;
	dp[index][m][k] = h;
	int ans = -1, hp;
	for (int i = 1; i <= n; i++) {
		
		for (int M = m; M > 0; M--) {
			for (int K = k; K >= 0; K--) {
				if (dp[index][M][K] <= b[i]) {
					ans = i;
					break;
				}
				if (dp[index][M][K] > h) continue;
				if (M > a[i])
					update_min(dp[index ^ 1][M - a[i]][K], dp[index][M][K] - b[i]);
				if (K > 0)
					update_min(dp[index ^ 1][M][K - 1], dp[index][M][K]);
				hp = min(m, M + c[i]);
				if (hp > a[i])
					update_min(dp[index ^ 1][hp - a[i]][K], dp[index][M][K]);

			}
			if (ans > 0) break;
		}
		if (ans > 0) break;
		memset(dp[index], 127, sizeof(dp[index]));
		index ^= 1;
	}
	if (ans > 0)
		printf("%d", ans);
	else
		printf("Fail");
	return 0;
}