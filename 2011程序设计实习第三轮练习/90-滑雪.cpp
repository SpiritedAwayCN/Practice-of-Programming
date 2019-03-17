#include<iostream>
constexpr int MAXN = 105;
using namespace std;

int dp[MAXN][MAXN], R, C;
int gmap[MAXN][MAXN], dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
int dfs(int x, int y) {
	if (x<1 || y<1 || x>R || y>C) return 0;
	if (dp[x][y]) return dp[x][y];
	int sx = x, sy = y, temp, tmax = 0;
	for (int i = 0; i < 4; i++) {
		sx = x, sy = y;
		sx += dir[i][0];
		sy += dir[i][1];
		if (gmap[sx][sy] < gmap[x][y]) {
			temp = dfs(sx, sy);
			if (temp > tmax) tmax = temp;
		}
	}
	dp[x][y] = tmax + 1;
	return dp[x][y];
}

int main() {
	cin >> R >> C;
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++) {
			cin >> gmap[i][j];
		}
	int max_len = 0,temp;
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++) {
			temp = dfs(i, j);
			if (temp > max_len)
				max_len = temp;
		}
	cout << max_len;
	return 0;
}