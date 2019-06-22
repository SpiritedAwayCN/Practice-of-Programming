#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
int map[35][35][35], l, m, n;
int sx, sy, sz, tx, ty, tz, ans;
struct Coordinate{
	int z, x, y;
};
queue<Coordinate> BFS_queue;

inline bool push_queue(int z, int x, int y, int step) {
	if (z<1 || z>l || x<1||x>m || y<1 || y>n) return false;
	if (map[z][x][y]) return false;
	if (tz == z&&tx == x&&ty == y) {
		ans = step;
		return true;
	}
	map[z][x][y] = ++step;
	BFS_queue.push(Coordinate{ z,x,y });
	return false;
}

int main() {
	char input;
	while (scanf("%d%d%d", &l, &m, &n)!=EOF) {
		if (l == 0) break;
		memset(map, 0, sizeof(map));
		ans = -1;
		while (!BFS_queue.empty()) BFS_queue.pop();

		for (int i = 1; i <= l; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 1; k <= n; k++) {
					cin >> input;
					switch (input) {
					case 'S':
						sz = i; sx = j; sy = k;
						break;
					case 'E':
						tz = i; tx = j; ty = k;
						break;
					case '#':
						map[i][j][k] = -1;
					}
				}
		map[sz][sx][sy] = 1;
		BFS_queue.push(Coordinate{ sz,sx,sy });
		while (!BFS_queue.empty()) {
			Coordinate current = BFS_queue.front();
			BFS_queue.pop();
			if (push_queue(current.z - 1, current.x, current.y, map[current.z][current.x][current.y])) break;
			if (push_queue(current.z + 1, current.x, current.y, map[current.z][current.x][current.y])) break;
			if (push_queue(current.z, current.x - 1, current.y, map[current.z][current.x][current.y])) break;
			if (push_queue(current.z, current.x + 1, current.y, map[current.z][current.x][current.y])) break;
			if (push_queue(current.z, current.x, current.y - 1, map[current.z][current.x][current.y])) break;
			if (push_queue(current.z, current.x, current.y + 1, map[current.z][current.x][current.y])) break;
		}
		if (ans != -1) {
			printf("Escaped in %d minute(s).\n", ans);
		}
		else {
			printf("Trapped!\n");
		}
	}
	return 0;
}