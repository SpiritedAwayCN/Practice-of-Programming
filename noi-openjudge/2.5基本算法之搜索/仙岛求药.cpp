#include<cstdio>
#include<queue>
#include<iostream>
using namespace std;
int map[25][25], sx, sy, tx, ty;
int m, n, ans;
struct Coordinate{
	int x, y;
};
queue<Coordinate> BFS_queue;

inline bool push_queue(int x, int y, int step) {
	if (x<1 || y<1 || x>m || y>n) return false;
	if (map[x][y]) return false;
	if (x == tx && y == ty) {
		ans = step;
		return true;
	}
	map[x][y] = ++step;
	BFS_queue.push(Coordinate{ x,y });
	return false;
}

int main() {
	char input;
	while (scanf("%d%d", &m, &n) != EOF) {
		if (m == 0)break;
		ans = -1;
		memset(map, 0, sizeof(map));
		while (!BFS_queue.empty()) BFS_queue.pop();
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> input;
				switch (input){
				case '#':
					map[i][j] = -1;
					break;
				case '@':
					sx = i; sy = j;
					break;
				case '*':
					tx = i; ty = j;
					break;
				}
			}
		}
		BFS_queue.push(Coordinate{ sx,sy });
		map[sx][sy] = 1;
		while (!BFS_queue.empty()) {
			Coordinate current = BFS_queue.front();
			BFS_queue.pop();
			if (push_queue(current.x - 1, current.y, map[current.x][current.y])) break; 
			if (push_queue(current.x + 1, current.y, map[current.x][current.y])) break;
			if (push_queue(current.x, current.y - 1, map[current.x][current.y])) break;
			if (push_queue(current.x, current.y + 1, map[current.x][current.y])) break;
		}
		printf("%d\n", ans);
	}
	return 0;
}