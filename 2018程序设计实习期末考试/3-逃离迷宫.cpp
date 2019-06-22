#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
struct node {
	int x, y;
};
queue<node> BFS_queue;
int map[12][12], sx, sy, tx, ty, T, m;
bool flag;
inline bool push_queue(int x, int y, int step) {
	if (x<1 || y<1 || x>m || y>m) return false;
	if (map[x][y] || step > T) return false;
	if (tx == x && ty == y) { flag = true; return true; }
	map[x][y] = ++step;
	BFS_queue.push(node{ x,y });
	return false;
}

int main() {
	int K;
	char temp;
	scanf("%d", &K);
	while (K--) {
		memset(map, 0, sizeof(map));
		while (!BFS_queue.empty()) BFS_queue.pop();
		scanf("%d%d", &m, &T);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++) {
				cin >> temp;
				switch (temp) {
				case '#':
					map[i][j] = -1;
					break;
				case 'S':
					sx = i; sy = j;
					break;
				case 'E':
					tx = i; ty = j;
					break;
				}
			}
		map[sx][sy] = 1;
		BFS_queue.push(node{ sx,sy });
		flag = false;
		while (!BFS_queue.empty()) {
			node current = BFS_queue.front();
			BFS_queue.pop();
			if (push_queue(current.x - 1, current.y, map[current.x][current.y])) break;
			if (push_queue(current.x + 1, current.y, map[current.x][current.y])) break;
			if (push_queue(current.x, current.y - 1, map[current.x][current.y])) break;
			if (push_queue(current.x, current.y + 1, map[current.x][current.y])) break;
		}
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}