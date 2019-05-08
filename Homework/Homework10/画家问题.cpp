#include<cstdio>
#include<cstring>
constexpr int MAXN = 20;
int n, lant[MAXN][MAXN],temp[MAXN][MAXN],ans = 0x7ffffff0;

inline void press_key(int x, int y) {
	temp[x][y]++;
	temp[x + 1][y]++;
	temp[x - 1][y]++;
	temp[x][y + 1]++;
	temp[x][y - 1]++;
}

int main() {
	char ch;
	int cnt;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		getchar();
		for (int j = 1; j <= n; j++) {
			ch = getchar();
			if (ch == 'y') lant[i][j] = 1;
		}
	}
	for (int status = 0; status < 1 << n; status++) {
		memcpy(temp, lant, sizeof(lant));
		cnt = 0;
		for (int j = 0; j < n; j++) {
			if (status&(1 << j)) press_key(1, j + 1), cnt++;
		}
		for (int i = 1; i <= n - 1; i++) {
			for (int j = 1; j <= n; j++) {
				if (1 != temp[i][j]%2)
					press_key(i + 1, j), cnt++;
			}
		}
		int j;
		for (j = 1; j <= n; j++)
			if (temp[n][j] % 2 != 1) break;
		if (j > n && ans > cnt) ans = cnt;
	}
	if (ans > 10000)
		printf("inf");
	else
		printf("%d", ans);
	return 0;
}