#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
using namespace std;
constexpr int MAXM = 9;
constexpr int MAXN = 16;
int n,number_map[MAXM][MAXM],sum_map[MAXM][MAXM];
double min_sigma = 1e12;
vector<int> store_sum;

int get_sum(int sx, int sy, int ex, int ey) {
	return sum_map[ex][ey] - sum_map[sx - 1][ey] - sum_map[ex][sy - 1] + sum_map[sx - 1][sy - 1];

}
double calc_sigma() {
	double aver = 0, sigma = 0;
	for (int i = 0; i < store_sum.size(); i++) {
		aver = (aver * i + store_sum[i]) / (i + 1);
	}
	for (int i = 0; i < store_sum.size(); i++) {
		sigma += (store_sum[i] - aver)*(store_sum[i] - aver);
	}
	sigma /= n;
	return sqrt(sigma);
}
void dfs(int sx,int sy,int ex,int ey,int left) {
	if (left == 1) {
		store_sum.push_back(get_sum(sx, sy, ex, ey));
		double temp = calc_sigma();
		if (temp < min_sigma)
			min_sigma = temp;
		store_sum.pop_back();
		return;
	}
	for (int i = sx + 1; i <= ex; i++) {
		//一行一行分
		store_sum.push_back(get_sum(i, sy, ex, ey));
		dfs(sx, sy, i - 1, ey, left - 1);
		store_sum.pop_back();
		store_sum.push_back(get_sum(sx, sy, i - 1, ey));
		dfs(i, sy, ex, ey, left - 1);
		store_sum.pop_back();
	}
	for (int j = sy + 1; j <= ey; j++) {
		//一列一列分
		store_sum.push_back(get_sum(sx, j, ex, ey));
		dfs(sx, sy, ex, j - 1, left - 1);
		store_sum.pop_back();
		store_sum.push_back(get_sum(sx, sy, ex, j - 1));
		dfs(sx, j, ex, ey, left - 1);
		store_sum.pop_back();
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) {
			cin >> number_map[i][j];
		}
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) {
			sum_map[i][j] = sum_map[i - 1][j] + sum_map[i][j - 1] - sum_map[i - 1][j - 1] + number_map[i][j];
		}
	dfs(1, 1, 8, 8, n);
	cout <<fixed<<setprecision(3)<< min_sigma;
	return 0;
}