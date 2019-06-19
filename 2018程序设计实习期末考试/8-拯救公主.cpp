#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
struct node{
	int x, y, bat, step;
};
queue<node> BFS_queue;
constexpr int MAXN = 105;
short vis[MAXN][MAXN][11], ans = -1;
int map[MAXN][MAXN], n, m, v, sx, sy, tx, ty;
int dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };

inline bool CoordValid(int x, int y) {
	return x > 0 && x <= n && y > 0 && y <= m;
}
bool push_queue(node current, int dir, bool jump = false) {
	if (!jump) {
		current.x += dx[dir];
		current.y += dy[dir];
		current.step++;
	}
	else {
		current.x = max(1, current.x);
		current.y = max(1, current.y);
		current.x = min(n, current.x);
		current.y = min(m, current.y);
	}
	if (current.x == tx && current.y == ty) {
		ans = current.step;
		return true;
	}
	if (!CoordValid(current.x,current.y)) return false;
	if (map[current.x][current.y] == -1) return false;
	if (map[current.x][current.y] == 0 && vis[current.x][current.y][current.bat]) return false;
	if (map[current.x][current.y] == 1 && (vis[current.x][current.y][current.bat]&(1<<dir))) return false;
	vis[current.x][current.y][current.bat] |= 1 << dir;
	BFS_queue.push(current); //不跳的情况
	if (map[current.x][current.y] == 1) {
		for (int battery = current.bat; battery >= 0; battery--) {
			if (push_queue(node{ current.x + dx[dir] * battery, current.y + dy[dir] * battery,
				battery, current.step }, dir, true)) return true;
		}
	}

	return false;
}

int main() {
	int cnt = 0;
	while (scanf("%d%d%d", &n, &m, &v) != EOF) {
		if (n == 0) break;
		ans = -1;
		memset(vis, 0, sizeof(vis));
		memset(map, 0, sizeof(map));
		while (!BFS_queue.empty()) BFS_queue.pop();
		char input;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				cin >> input;
				switch (input){
				case 'E':
					map[i][j] = 1;
					break;
				case 'S':
					sx = i; sy = j;
					break;
				case 'T':
					tx = i; ty = j;
					break;
				case '#':
					map[i][j] = -1;
				}
			}
		BFS_queue.push(node{ sx,sy,v,0});
		vis[sx][sy][v] = 15;
		while (!BFS_queue.empty()) {
			node current = BFS_queue.front();
			BFS_queue.pop();
			for (int d = 0; d < 4; d++)
				if (push_queue(current, d)) break;
			if (ans > 0) break;
		}
		printf("Case #%d: %d\n",++cnt, ans);
	}
	return 0;
}