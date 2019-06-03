#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 105, MAXK = 105;
int lake[MAXN][MAXN], n, m, k, cnt;

void dfs(int x, int y) {
	if (x<1 || y<1 || x>n || y>m) return;
	if (lake[x][y]) return;
	lake[x][y] = ++cnt;
	dfs(x - 1, y);
	dfs(x + 1, y);
	dfs(x, y + 1);
	dfs(x, y - 1);
}

int main() {
	memset(lake, -1, sizeof(lake));
	scanf("%d%d%d", &n, &m, &k);
	int tempx, tempy;
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", &tempx, &tempy);
		lake[tempx][tempy] = 0;
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cnt = 0;
			dfs(i, j);
		}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			ans = max(ans, lake[i][j]);
	printf("%d", ans);
	return 0;
}