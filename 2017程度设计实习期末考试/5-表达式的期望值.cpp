#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 205;
double P[MAXN], pb[MAXN][20];
//pb[i][bit] 前i个数的表达式 第bit位是1的概率
int a[MAXN];
char oper[MAXN];
int n;
int main() {
	int cnt = 0;
	while (scanf("%d", &n) != EOF) {
		n++;
		++cnt;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i < n; i++)
			cin >> oper[i];
		for (int i = 1; i < n; i++)
			scanf("%lf", &P[i]);
		
		for (int bit = 0; bit < 20; bit++) {
			pb[1][bit] = (a[1] >> bit) & 1;
			for (int i = 2; i <= n; i++) {
				int num = (a[i] >> bit) & 1;
				pb[i][bit] = P[i - 1] * pb[i - 1][bit];
				switch (oper[i-1])
				{
				case '|':
					pb[i][bit] += (1 - P[i - 1]) * pb[i - 1][bit];
					pb[i][bit] += (1 - P[i - 1]) * (1 - pb[i - 1][bit]) * num;
					break;
				case '&':
					pb[i][bit] += (1 - P[i - 1]) * pb[i - 1][bit] * (1 & num);
					break;
				case '^':
					pb[i][bit] += (1 - P[i - 1]) * pb[i - 1][bit] * (1 ^ num);
					pb[i][bit] += (1 - P[i - 1]) * (1 - pb[i - 1][bit]) * num;
					break;
				}
			}
		}
		double ans = 0;
		for (int bit = 0; bit < 20; bit++) {
			ans += pb[n][bit] * (1 << bit);
		}
		printf("Case %d:\n%f\n", cnt, ans);
	}
	return  0;
}
