#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
constexpr int MAXN = 105;

int map[MAXN][MAXN], n, m, ans;

bool dfs(int x, int y) {
	if (x<1 || y<1 || x>n || y>m) return false;
	if (map[x][y]) return false;
	map[x][y] = ans + 1;
	dfs(x - 1, y);
	dfs(x + 1, y);
	dfs(x, y - 1);
	dfs(x, y + 1);
	dfs(x + 1, y + 1);
	dfs(x + 1, y - 1);
	dfs(x - 1, y - 1);
	dfs(x - 1, y + 1);
	return true;
}

int main() {
	char temp;
	while (scanf("%d%d", &n, &m) != EOF) {
		if (n == 0) break;
		memset(map, 0, sizeof(map));
		ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				cin >> temp;
				if (temp == '*') map[i][j] = -1;
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (dfs(i, j)) ans++;
			}
		printf("%d\n", ans);
	}

	return 0;
}