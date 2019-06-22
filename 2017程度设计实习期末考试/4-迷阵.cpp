#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
constexpr int MAXN = 260;

int map[MAXN][MAXN], m, n, h, ans;
bool vis[MAXN][MAXN][6];
struct Coordinate {
	int x, y, hp, step;
};
queue<Coordinate> BFS_queue;

inline bool push_queue(int dx, int dy, Coordinate current) {
	int x = current.x + dx, y = current.y + dy;
	if (x<1 || y<1 || x>m || y>n) return false;
	if (x == m && y == n) {
		ans = current.step + 1;
		return true;
	}
	if (map[x][y] == -1) return false;
	if (map[x][y] == -2) current.hp -= 1;
	if (current.hp <= 0) return false;
	if (vis[x][y][current.hp]) return false;
	vis[x][y][current.hp] = true;
	current.x = x; current.y = y;
	current.step++;
	BFS_queue.push(current);
	return false;
}

int main() {
	char temp;
	int T;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		scanf("%d%d%d", &m, &n, &h);
		memset(map, 0, sizeof(map));
		memset(vis, 0, sizeof(vis));
		while (!BFS_queue.empty()) BFS_queue.pop();

		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++) {
				cin >> temp;
				if (temp == '#') map[i][j] = -1;
				else if (temp == '*') map[i][j] = -2;
			}
		BFS_queue.push(Coordinate{ 1,1, h,0 });
		vis[1][1][h] = true;
		while (!BFS_queue.empty()) {
			Coordinate current = BFS_queue.front();
			BFS_queue.pop();
			if (push_queue(-1, 0, current)) break;
			if (push_queue(1, 0, current)) break;
			if (push_queue(0, -1, current)) break;
			if (push_queue(0, 1, current)) break;
		}
		printf("%d\n", ans);
	}

	return 0;
}