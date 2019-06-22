#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int S, income[16], cost[16];
//烂方法，别学
struct Backpack {
	int mw1, mw2;
	int** dp;
	Backpack(int _w1, int _w2) :mw1(_w1), mw2(_w2) {
		dp = new int*[mw1 + 1];
		for (int i = 0; i <= mw1; i++) {
			dp[i] = new int[mw2 + 1];
			memset(dp[i], 0, sizeof(int)*(mw2 + 1));
		}
	}
	~Backpack() {
		for (int i = 0; i <= mw1; i++)
			delete[] dp[i];
		delete[] dp;
	}
	int solve() {
		for (int i = 1; i <= 10; i++)
			for (int j = mw1; j >= cost[i]; j--)
				for (int k = mw2; k >= 1; k--)
					dp[j][k] = max(dp[j][k], dp[j - cost[i]][k - 1] + income[i]);
		return dp[mw1][mw2];
	}

};


int main() {
	int aans = 0;
	scanf("%d", &S);
	for (int i = 1; i <= 15; i++)
		scanf("%d%d", &income[i], &cost[i]);
	for (int st = 1; st < 32; st++) {
		int day = 0, cs = 0, ans = 0;
		for (int i = 0; i < 5; i++)
			if ((st >> i) & 1) {
				day++;
				cs += cost[11 + i];
				ans += income[11 + i];
			}
		if (cs > S) continue;
		if (cs == S) {
			aans = max(aans, ans);
			continue;
		}
		Backpack calc(S - cs, day);
		ans += calc.solve();
		aans = max(aans, ans);
	}
	printf("%d\n", aans);
	return 0;
}