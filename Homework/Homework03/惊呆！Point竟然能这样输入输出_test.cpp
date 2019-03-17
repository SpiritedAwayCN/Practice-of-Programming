#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point():x(1),y(2) { };
friend istream& operator >> (istream& ist,Point &pt){
        ist>>pt.x>>pt.y;
        return ist;
    }
    friend ostream& operator << (ostream& ost,const Point &pt){
        ost<<pt.x<<','<<pt.y;
        return ost;
    }
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << Point() << endl;
	 }
	return 0;
}
