#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
class Coordinate {
public:
	int x;
	int y;
	bool valid() const{
		return x >= 1 && x <= 5 && y >= 1 && y <= 5;
	}
	friend ostream& operator<<(ostream& ost, const Coordinate& B) {
		ost << '(' << B.x - 1 << ", " << B.y - 1 << ')';
		return ost;
	}
};


queue<Coordinate> BFS_queue;
vector<Coordinate> ans;
int map[6][6];
inline bool push_queue(const Coordinate& curr, int step) {
	if (!curr.valid()) return false;
	if (map[curr.x][curr.y] != 0) return false;
	map[curr.x][curr.y] = step + 1;
	if (curr.x == 5 && curr.y == 5) return true;
	BFS_queue.push(curr);
	return false;
}

int main() {
	int step;
	for (int i = 1; i <= 5; i++)
		for (int j = 1; j <= 5; j++) {
			scanf("%d", &map[i][j]);
			map[i][j] *= -1;
		}
	bool flag = false;
	BFS_queue.push(Coordinate{ 1,1 });
	map[1][1] = 1;
	while (!BFS_queue.empty()) {
		Coordinate curr = BFS_queue.front();
		BFS_queue.pop();
		step = map[curr.x][curr.y];
		flag |= push_queue(Coordinate{ curr.x + 1,curr.y }, step);
		flag |= push_queue(Coordinate{ curr.x - 1,curr.y }, step);
		flag |= push_queue(Coordinate{ curr.x,curr.y + 1 }, step);
		flag |= push_queue(Coordinate{ curr.x,curr.y - 1 }, step);
		if (flag) break;
	}
	Coordinate curr = Coordinate{ 5,5 }, temp;
	while (curr.x != 1 || curr.y != 1) {
		int dis = map[curr.x][curr.y];
		ans.push_back(curr);
		temp.x = curr.x - 1; temp.y = curr.y;
		if (temp.valid() && dis > map[temp.x][temp.y] && map[temp.x][temp.y] != -1) { curr = temp; continue; }
		temp.x = curr.x + 1; temp.y = curr.y;
		if (temp.valid() && dis > map[temp.x][temp.y] && map[temp.x][temp.y] != -1) { curr = temp; continue; }
		temp.x = curr.x; temp.y = curr.y + 1;
		if (temp.valid() && dis > map[temp.x][temp.y] && map[temp.x][temp.y] != -1) { curr = temp; continue; }
		temp.x = curr.x; temp.y = curr.y - 1;
		if (temp.valid() && dis > map[temp.x][temp.y] && map[temp.x][temp.y] != -1) { curr = temp; continue; }
	}
	ans.push_back(curr);
	for (auto iter = ans.rbegin(); iter != ans.rend(); iter++) {
		cout << *iter << endl;
	}
	return 0;
}