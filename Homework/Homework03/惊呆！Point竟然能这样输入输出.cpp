#include <iostream>
using namespace std;
class Point {
	private:
		int x;
		int y;
	public:
		Point() { };
// 在此处补充你的代码
    friend istream& operator >> (istream& ist,Point &pt){
        ist>>pt.x>>pt.y;
        return ist;
    }
    friend ostream& operator << (ostream& ost,Point &pt){
        ost<<pt.x<<','<<pt.y;
        return ost;
    }
};
int main()
{
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}
