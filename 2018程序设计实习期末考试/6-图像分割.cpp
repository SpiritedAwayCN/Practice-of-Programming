#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 55;
int h, w, m, map[MAXN][MAXN], zone[MAXN][MAXN];
int cnt, dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };

inline bool isValid(int x, int y) {
	if (x<1 || y<1 || x>h || y>w) return false;
	return true;
}

void dfs(int x, int y) {
	if (!isValid(x, y)) return;
	if (zone[x][y]) return;

	zone[x][y] = cnt;
	for (int i = 0; i < 4; i++) {
		if (!isValid(x + dx[i], y + dy[i])) continue;
		if (abs(map[x + dx[i]][y + dy[i]] - map[x][y]) <= m)
			dfs(x + dx[i], y + dy[i]);
	}
}

int main() {
	while (scanf("%d%d%d", &h, &w, &m) != EOF) {
		if (h == 0) break;
		cnt = 0;
		memset(zone, 0, sizeof(zone));
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				scanf("%d", &map[i][j]);

		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++) {
				if (!zone[i][j]) {
					++cnt;
					dfs(i, j);
				}
			}
		printf("%d\n", cnt);
	}
	return 0;
}