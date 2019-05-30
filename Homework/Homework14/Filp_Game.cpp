#include<cstdio>
#include<queue>
using namespace std;
queue<int> BFS_queue;
bool vis[1 << 16];
// 第16位起，存步数

inline bool change_bit(int& num, int row, int column) {
	if (row < 0 || column < 0 || row>3 || column>3) return false;
	num ^= 1 << (row * 4 + column);
	return true;
}

inline bool push_queue(int curr) {
	//目前只变了前16位，step的后16位没变
	if (vis[curr & 0x0000ffff]) return false;
	if ((curr & 0x0000ffff) == 0 || (curr & 0x0000ffff) == ((1 << 16) - 1)) return true;
	curr += 1 << 16; //步数+1
	BFS_queue.push(curr);
	vis[curr & 0x0000ffff] = true;
	return false;
}

int main() {
	int init = 0, ans = 0, temp;
	char input_char;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			input_char = getchar();
			if (input_char == 'b')
				init |= 1 << (i * 4 + j);
		}
		getchar();
	}
	if (init == 0 || init == 0x0000ffff) {
		printf("0");
		return 0;
	}
	BFS_queue.push(init);
	vis[init] = true;
	bool flag = false;
	while (!BFS_queue.empty()) {
		int curr = BFS_queue.front();
		BFS_queue.pop();
		ans = curr >> 16;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp = curr;
				change_bit(temp, i, j);
				change_bit(temp, i + 1, j);
				change_bit(temp, i - 1, j);
				change_bit(temp, i, j + 1);
				change_bit(temp, i, j - 1);
				if (push_queue(temp)) { flag = true; break; }

			}
			if (flag) break;
		}
		if (flag) break;
	}
	if (flag)
		printf("%d", ++ans);
	else
		printf("Impossible");
	return 0;
}