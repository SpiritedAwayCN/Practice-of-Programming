#include <iostream>
using namespace std;
class MyCin
{
public:
    MyCin():tag(true){}
    friend MyCin& operator >>(MyCin& mc,int &num){
        if(!mc.tag) return mc;
        if(!(cin>>num)) mc.tag = false;
        if(num==-1) mc.tag = false;
        return mc;
    }
    operator bool(){
        return tag;
    }
private:
    bool tag;
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2)
        cout  << n1 << " " << n2 << endl;
    return 0;
}
