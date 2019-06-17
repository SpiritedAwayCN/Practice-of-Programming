#include<cstdio>
#include<string>
#include<iostream>
#include<cstring>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
struct node {
	long long number;
	int step;
};
map<long long, long long> vis;
queue<node> BFS_queue;
long long s, t;
int cnt;
string ans;
inline bool push_queue(long long num, long long pred, int step) {
	//25步以内*3不会溢出
	if (vis.find(num) != vis.end()) return false;
	vis.insert(make_pair(num, pred));
	if (num == t) {
		cnt = step + 1;
		return true;
	}
	BFS_queue.push(node{ num,++step });
	return false;
}

int main() {
	while (scanf("%lld%lld", &s, &t) != EOF) {
		if (s == 0 && t == 0) break;
		vis.clear();
		ans.clear();
		while (!BFS_queue.empty()) BFS_queue.pop();

		BFS_queue.push(node{ s,0 });
		vis.insert(make_pair(s, -1));
		while (!BFS_queue.empty()) {
			node num = BFS_queue.front();
			BFS_queue.pop();
			if (push_queue(num.number * 3, num.number, num.step)) break;
			if (push_queue(num.number >> 1, num.number, num.step)) break;

		}
		long long last = t, pred;
		while (last != s) {
			pred = vis.at(last);
			ans += pred > last ? 'O' : 'H';
			last = pred;
		}
		reverse(ans.begin(), ans.end());
		cout << cnt << '\n' << ans << endl;
	}
	return 0;
}