#include<cstdio>
int ans;
void dfs(int n, int m, int l) {
	if (m == 1 || n == 0) {
		if (l >= n) {
			ans++;
		}
		return;
	}
	if (l > n) l = n;
	for (int i = l; i > 0; i--) {
		dfs(n - i, m - 1, i);
	}
		
}

int main() {
	int T;
	int n, m;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		scanf("%d%d", &n, &m);
		dfs(n, m, n);
		printf("%d\n", ans);
	}
	return 0;
}