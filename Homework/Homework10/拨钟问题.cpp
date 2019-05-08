#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int clockmap[5][5],temp[5][5], answer[50], ans = 0x7ffffff0;
vector<int> solution;
inline void operate_key(int x, int y) {
	temp[x][y]++;
	temp[x - 1][y]++;
	temp[x + 1][y]++;
	temp[x][y - 1]++;
	temp[x][y + 1]++;
	if ((x == 2) + (y == 2) == 1)
		temp[2][2]--;
	else if (x != 2 && y != 2) {
		temp[2][2]++;
	}
	solution.push_back(3 * (x - 1) + y);
}
int main() {
	//枚举边角
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			scanf("%d", &clockmap[i][j]);
	for (int sta = 0; sta < 1 << 8; sta++) {
		memcpy(temp, clockmap, sizeof(clockmap));
		solution.clear();
		for (int cnt = 0; cnt < (sta & 3); cnt++)
			operate_key(1, 1);
		for (int cnt = 0; cnt < ((sta>>2) & 3); cnt++)
			operate_key(1, 3);
		for (int cnt = 0; cnt < ((sta>>4) & 3); cnt++)
			operate_key(3, 1);
		for (int cnt = 0; cnt < ((sta>>6) & 3); cnt++)
			operate_key(3, 3);

		while (temp[2][2] % 4) operate_key(2, 2);
		while (temp[1][2] % 4) operate_key(1, 2);
		while (temp[3][2] % 4) operate_key(3, 2);
		while (temp[2][1] % 4) operate_key(2, 1);
		while (temp[2][3] % 4) operate_key(2, 3);
		if (temp[1][1] % 4 == 0 && temp[3][1] % 4 == 0
			&& temp[1][3] % 4 == 0 && temp[3][3] % 4 == 0
			&& ans>solution.size()) {
			ans = solution.size();
			for (int i = 0; i < ans; i++)
				answer[i] = solution[i];
		}
	}
	sort(answer, answer + ans);
	for (int i = 0; i < ans; i++)
		printf("%d ", answer[i]);
	return 0;
}