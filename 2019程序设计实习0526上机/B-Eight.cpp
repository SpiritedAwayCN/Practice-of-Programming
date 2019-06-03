#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
#include<stdexcept>
#include<vector>
using namespace std;
constexpr int ten[] = { 1,10,100,1000,10000,100000,1000000,10000000,100000000 };
//注：略无脑
class Board {
public:
	Board(int _num) :num(_num){}
	bool move_blank(int side) {
		//0上 1下 2左 3右
		int index = 0, dist, temp = num;
		while (temp % 10) {
			index++;
			temp /= 10;
		}

		switch (side){
		case 0:
			dist = index + 3;
			if (dist > 8) return false;
			break;
		case 1:
			dist = index - 3;
			if (dist < 0) return false;
			break;
		case 2:
			dist = index + 1;
			if (dist % 3 == 0) return false;
			break;
		case 3:
			if (index % 3 == 0) return false;
			dist = index - 1;
			break;
		}
		int bit = num / ten[dist];
		bit %= 10;
		num -= bit * ten[dist];
		num += bit * ten[index];
		return true;
	}
	bool operator<(const Board& B) const {
		return num < B.num;
	}
	int num;
};
map<Board, short> vis;
queue<Board> BFS_queue;
vector<char> solution;
inline char id2char(int dir) {
	if (dir == 0) return 'u';
	if (dir == 1) return 'd';
	if (dir == 2) return 'l';
	return 'r';
}

int main() {
	int init = 0;
	bool flag = false;
	char ch;
	for (int i = 1; i <= 9; i++) {
		cin >> ch;
		init *= 10;
		if (ch != 'x') init += ch - '0';
	}
	BFS_queue.push(Board(init));
	vis.insert(make_pair(Board(init) , -1));
	while (!BFS_queue.empty()) {
		Board current = BFS_queue.front();
		Board temp = current;
		BFS_queue.pop();
		for (int dir = 0; dir < 4; dir++) {
			temp = current;
			if (temp.move_blank(dir)) {
				if (vis.find(temp) != vis.end()) continue;
				vis.insert(make_pair(temp, dir));
				if (temp.num == 123456780) {
					flag = true;
					break;
				}
				BFS_queue.push(temp);
			}
		}
		if (flag) break;
	}
	if (!flag) {
		cout << "unsolvable";
	}
	else {
		Board current(123456780);
		while (current.num != init) {
			int dir = vis.at(current);
			solution.push_back(id2char(dir));
			if (!current.move_blank(dir ^ 1))
				throw runtime_error("error!"); //调试用
		}
		for (int i = solution.size() - 1; i >= 0; i--)
			cout << solution[i];
	}
	return 0;
}