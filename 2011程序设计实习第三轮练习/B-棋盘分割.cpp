#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<cstring>
constexpr int LEN = 8;
constexpr int INF = 1 << 25;
using namespace std;
int R, C, gmap[LEN + 1][LEN + 1], smap[LEN + 1][LEN + 1];
int n, dp[LEN + 1][LEN + 1][LEN +1][LEN + 1][16];
double aver = 0;
int sq_sum(int sx, int sy, int ex, int ey) {
	return smap[ex][ey] - smap[sx - 1][ey] - smap[ex][sy - 1] + smap[sx - 1][sy - 1];
}

int dfs(int sx,int sy,int ex,int ey, int k) {
	//if (sx<1 || sy<1 || ex>LEN || ey>LEN) return INF;
	if (dp[sx][sy][ex][ey][k]!=-1) return dp[sx][sy][ex][ey][k];
	if (k == 1) {
		dp[sx][sy][ex][ey][k] = sq_sum(sx, sy, ex, ey);
		dp[sx][sy][ex][ey][k] *= dp[sx][sy][ex][ey][k];
		return dp[sx][sy][ex][ey][k];
	}
	int cut_row = INF,temp,ups,bps;
	for (int i = sx + 1; i <= ex; i++) {
		ups = sq_sum(i, sy, ex, ey);
		bps = sq_sum(sx, sy, i - 1, ey);
		temp = min(dfs(sx, sy, i - 1, ey, k - 1) + ups * ups, dfs(i, sy, ex, ey, k - 1) + bps * bps);
		cut_row = min(cut_row, temp);
	}
	for (int j = sy + 1; j <= ey; j++) {
		ups = sq_sum(sx, j, ex, ey);
		bps = sq_sum(sx, sy, ex, j - 1);
		temp = min(dfs(sx, sy, ex, j - 1, k - 1) + ups * ups, dfs(sx, j, ex, ey, k - 1) + bps * bps);
		cut_row = min(cut_row, temp);
	}
	dp[sx][sy][ex][ey][k] = cut_row;
	return cut_row;
}

int main() {
	cin >> n;
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= LEN; i++)
		for (int j = 1; j <= LEN; j++) {
			cin >> gmap[i][j];
			aver += gmap[i][j];
		}
	aver /= n;
	for (int i = 1; i <= LEN; i++)
		for (int j = 1; j <= LEN; j++)
			smap[i][j] = gmap[i][j] + smap[i - 1][j] + smap[i][j - 1] - smap[i - 1][j - 1];
	int min_squr = dfs(1, 1, LEN, LEN, n);
	double ans = min_squr * 1.0 / n - aver * aver;
	cout <<fixed << setprecision(3)<< sqrt(ans);
	return 0;
}