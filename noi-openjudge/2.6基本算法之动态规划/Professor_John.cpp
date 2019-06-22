#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 30;
constexpr int INF = 0x3f3f3f3f;
int dist[MAXN][MAXN], inp[MAXN][MAXN];
bool vis[MAXN];
//Floyd
int main() {
	int T, m, n = 0;
	char cap1, cap2,oper;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		memset(dist, 0x3f, sizeof(dist));
		memset(vis, 0, sizeof(vis));
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			getchar();
			cap1 = getchar();
			oper = getchar();
			cap2 = getchar();
			if (oper == '>') swap(cap1, cap2);
			dist[cap1 - 'A' + 1][cap2 - 'A' + 1] = 1;
			inp[cap1 - 'A' + 1][cap2 - 'A' + 1] = 1;
			n = max(n, cap1 - 'A' + 1);
			n = max(n, cap2 - 'A' + 1);
			vis[cap1 - 'A' + 1] = true;
			vis[cap2 - 'A' + 1] = true;
		}
		for (int i = 1; i <= n; i++)
			dist[i][i] = 0;

		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++) {
					if (dist[i][j] > dist[i][k] + dist[k][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
		int cnt = 0;
		printf("Case %d:\n", tt);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j && vis[i] && vis[j] && dist[i][j] < 30 && inp[i][j] == 0) {
					++cnt;
					printf("%c<%c\n", i - 1 + 'A', j - 1 + 'A');
				}
		if (!cnt) {
			printf("NONE\n");
		}
	}

	return 0;
}