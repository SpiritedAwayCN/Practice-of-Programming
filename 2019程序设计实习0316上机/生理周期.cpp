#include<iostream>

using namespace std;
const int table[] = {23,28,33};

int main(){
    int day=0,a[3],ans;
    cin>>a[0]>>a[1]>>a[2]>>ans;
    for(int i=0;i<3;i++){
        a[i] = table[i] - a[i]%table[i];
    }

    while(a[0]||a[1]||a[2]){
        day++;
        for(int i=0;i<3;i++){
            a[i]++;
            a[i]%=table[i];
        }
    }
    ans = day - ans;
    ans %= 21252;
    while(ans<=0) ans+=21252;
    printf("%d",ans);
    return 0;
}
