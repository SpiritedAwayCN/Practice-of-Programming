#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
constexpr int MAXN = 200001;
int vis[MAXN], n,k;
queue<int> BFS_queue;
inline bool push_queue(int index,int step) {
	if (index < 0 || index >= MAXN) return false;
	if (vis[index] != -1) return false;
	vis[index] = step + 1;
	if (index == k) return true;
	BFS_queue.push(index);
	return false;
}

int main() {
	int index;
	scanf("%d%d", &n, &k);
	memset(vis, -1, sizeof(vis));
	vis[n] = 0;
	BFS_queue.push(n);
	while (!BFS_queue.empty()) {
		index = BFS_queue.front();
		BFS_queue.pop();
		if (push_queue(index + 1, vis[index])) break;
		if (push_queue(index - 1, vis[index])) break;
		if (push_queue(index << 1, vis[index])) break;
	}
	printf("%d", vis[k]);
	return 0;
}