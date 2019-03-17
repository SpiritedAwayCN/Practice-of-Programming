#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
public:
    Array2()
    : row(0)
    , column(0)
    , p(NULL)
    {
    }
    Array2(int x,int y)
    : row(x)
    , column(y)
    {
        p = new int[x*y];
    }
    ~Array2(){
        delete[] p;
    }
    int& operator()(int x,int y){
        return p[x*column+y];
    }
    int* operator[](int x){
        return p + x*column;
    }
    Array2& operator=(const Array2& ary){
        if(p) delete[] p;
        row = ary.row;
        column = ary.column;
        p = new int[row*column];
        memcpy(p,ary.p,row*column*sizeof(int));
    }
private:
    int row;
    int column;
    int *p;
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
