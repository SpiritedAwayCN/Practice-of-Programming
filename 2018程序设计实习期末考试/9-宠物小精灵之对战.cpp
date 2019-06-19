#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 305;
bool res[MAXN][MAXN];
int dp[MAXN][MAXN],n;
/*
dp[i][j] 第i到j个精灵之间所有精灵对战(可能i>j),最后是否可能只剩下第i只
如果第i到第j个精灵间对战，最后可能只剩下第m(不等于i,j)号精灵
等价于 dp[m][i]&&dp[m][j]==true
即等价于 m既能在i~m中活到最后，也能在m~j中活到最后
*/
bool get_dp(int x, int y, int m) {
	//x~y号精灵对战，m活到最后 注意x与y顺序没有要求
	if (x == m && dp[x][y] != -1) return dp[x][y];
	if (y == m && dp[y][x] != -1) return dp[y][x];
	if (x != m && y != m)
		return get_dp(x, m, m) && get_dp(m, y, m);
	if (x > y) swap(x, y);
	if (x == m){
		if (y - x == 1) return dp[x][y] = res[x][y];
		for (int i = x + 1; i <= y; i++)
			if (res[m][i] && get_dp(x + 1, y, i)) {
				return dp[x][y] = 1;
			}
		return dp[x][y] = 0;
	}
	else {
		//y==m
		if (y - x == 1) return dp[y][x] = res[y][x];
		for (int i = x; i <= y - 1; i++)
			if (res[m][i] && get_dp(x, y - 1, i))
				return dp[y][x] = 1;
		return dp[y][x] = 0;
	}
}

int main() {
	char temp;
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> temp;
			if (i == j) continue;
			res[i][j] = temp == 'W' ? true : false;
		}
	for (int i = 1; i <= n; i++)
		if (get_dp(1, n, i))
			printf("%d ", i);
	return 0;
}