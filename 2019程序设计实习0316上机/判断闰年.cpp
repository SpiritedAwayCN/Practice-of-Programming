#include<iostream>
using namespace std;

int main(){
    int year;
    cin>>year;

    if( !(year%400) || (year%100 && year%4==0))
        cout<<"Y";
    else
        cout<<"N";

    return 0;
}
