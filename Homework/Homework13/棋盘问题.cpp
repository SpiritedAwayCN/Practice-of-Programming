#include<cstdio>
#include<cstring>
constexpr int MAXN = 10;
bool map[MAXN][MAXN], column[MAXN];
int n, k, ans;
void dfs(int line, int num) {
	//放第line行，还要放num个
	if (num == 0) { ans++; return; }
	if (n - line + 1 < num) return;

	dfs(line + 1, num); //这行不放
	for (int j = 1; j <= n; j++) {
		if (map[line][j] && !column[j]) {
			column[j] = true;
			dfs(line + 1, num - 1);
			column[j] = false;
		}
	}
}

int main() {
	char ch;
	while (true) {
		scanf("%d%d", &n, &k);
		if (n == -1) break;
		ans = 0;
		memset(map, 0, sizeof(map));
		memset(column, 0, sizeof(column));
		for (int i = 1; i <= n; i++) {
			getchar();
			for (int j = 1; j <= n; j++) {
				ch = getchar();
				if (ch == '#') map[i][j] = true;
				else map[i][j] = false;
			}
		}
		dfs(1, k);
		printf("%d\n", ans);
	}
	return 0;
}