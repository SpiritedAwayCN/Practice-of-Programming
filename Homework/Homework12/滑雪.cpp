#include<cstdio>
#include<cstring>

constexpr int MAXN = 105;
int dp[MAXN][MAXN],R, C, map[MAXN][MAXN];
int get_dp(int, int);

inline bool judge(int x, int y, int h) {
	if (x<1 || y<1 || x>R || y>C) return false;
	if (map[x][y] < h) return true;
	return false;
}
inline void excu(int x,int y, int h, int& ans) {
	if (!judge(x, y, h)) return;
	int temp = get_dp(x, y) + 1;
	if (temp > ans) ans = temp;
}

int get_dp(int x, int y) {
	if (dp[x][y] != -1) return dp[x][y];
	int ans = 1;
	excu(x - 1, y, map[x][y], ans);
	excu(x + 1, y, map[x][y], ans);
	excu(x, y - 1, map[x][y], ans);
	excu(x, y + 1, map[x][y], ans);
	dp[x][y] = ans;
	return dp[x][y];
}

int main() {
	scanf("%d%d", &R, &C);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			scanf("%d", &map[i][j]);
	int ans = 0;
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			if (ans < get_dp(i, j)) ans = dp[i][j];
	printf("%d", ans);
	return 0;
}