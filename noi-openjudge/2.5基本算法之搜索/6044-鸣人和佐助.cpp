#include<iostream>
#include<queue>
constexpr int MAXN = 205;
using namespace std;
int ans = -1, m, n, T, sx, sy, ex, ey;
bool gmap[MAXN][MAXN];
short vis[MAXN][MAXN];
struct node
{
	node(int _x,int _y,int _kla,int _step=0):x(_x),y(_y),kla(_kla),step(_step){}
	int x;
	int y;
	int kla;
	int step;
};
queue<node> que;

inline bool next_step(int x, int y, const node& last) {
	if (x == ex&&y == ey) {
		ans = last.step + 1;
		return true;
	}
	if (x<1 || y<1 || x>m || y>n) return false;
	int kela = last.kla;
	if (gmap[x][y]) kela--;
	if (kela < 0) return false;
	if (vis[x][y] & (1 << kela)) return false;
	vis[x][y] |= 1 << kela;
	que.push(node(x, y, kela, last.step + 1));
	return false;
}

int main() {
	cin >> m >> n >> T;
	char temp_c;
	//vis[i][j]-->有几个kla在该位置被搜索过，则二进制第几为设为1
	for (int i = 1; i <= m; i++) {
		cin.get();
		for (int j = 1; j <= n; j++) {
			temp_c = cin.get();
			switch (temp_c)
			{
			case '#':
				//enemy
				gmap[i][j] = true;
				break;
			case '@':
				//start
				sx = i; sy = j;
				break;
			case '+':
				ex = i; ey = j;
				break;
			}
		}
	}
	que.push(node(sx,sy,T));
	vis[sx][sy] = 1 << T;
	while (!que.empty()) {
		node current = que.front();
		que.pop();
		if (next_step(current.x - 1, current.y, current)) break;
		if (next_step(current.x + 1, current.y, current)) break;
		if (next_step(current.x, current.y + 1, current)) break;
		if (next_step(current.x, current.y - 1, current)) break;
	}
	cout << ans << endl;
	return 0;
}