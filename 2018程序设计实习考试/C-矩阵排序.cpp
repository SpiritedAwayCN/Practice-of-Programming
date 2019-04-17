#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat {
	int h, w;
public:
	Mat(int height, int width) :h(height), w(width)
		// 在此处补充你的代码
	{
		id = ++global;
		number = new int[h*w];
	}
	Mat(Mat&& A) {
		id = A.id;
		h = A.h;
		w = A.w;
		sum = A.sum;
		number = A.number;
		A.number = NULL;
	}
	~Mat() {
		if(number) delete[] number;
	}
	Mat& operator=(const Mat& A) {
		if (this == &A) return *this;
		id = A.id;
		h = A.h;
		w = A.w;
		sum = A.sum;
		if(number)delete[] number;
		number = new int[w*h];
		for (int i = 0; i < w*h; i++)
			number[i] = A.number[i];
		return *this;
	}
	friend istream& operator >>(istream& ist, Mat& A) {
		A.sum = 0;
		for (int i = 0; i < A.h; i++)
			for (int j = 0; j < A.w; j++) {
				ist >> *(A.number + i * A.w + j);
				A.sum += *(A.number + i * A.w + j);
			}
		return ist;
	}
	friend ostream& operator <<(ostream& ost, Mat& A) {
		for (int i = 0; i < A.h; i++) {
			for (int j = 0; j < A.w; j++)
				ost << *(A.number + i * A.w + j) << ' ';
			ost << endl;
		}
		return ost;
	}
	bool operator < (const Mat& B) {
		if(w*h!=B.h*B.w) return w * h < B.h*B.w;
		return id > B.id;
	}
	int sum;
	int id;
	static int global;
private:
	int* number;
};
int Mat::global = 0;
bool comparator_1(const Mat&A, const Mat&B) {
	if(A.sum!=B.sum) return A.sum < B.sum;
	return A.id > B.id;
}
struct comparator_2
{
	bool operator ()(const Mat&A, const Mat&B) const {
		return A.id < B.id;
	}
};
int main()
	{
		vector<Mat> m;
		m.push_back(Mat(2, 2));
		m.push_back(Mat(3, 4));
		m.push_back(Mat(2, 2));
		cin >> m[0] >> m[1] >> m[2];
		sort(m.begin(), m.end());
		cout << m[0] << endl << m[1] << endl << m[2] << endl;
		cout << "*************" << endl;
		sort(m.begin(), m.end(), comparator_1);
		cout << m[0] << endl << m[1] << endl << m[2] << endl;
		cout << "*************" << endl;
		sort(m.begin(), m.end(), comparator_2());
		cout << m[0] << endl << m[1] << endl << m[2] << endl;
		return 0;
	}