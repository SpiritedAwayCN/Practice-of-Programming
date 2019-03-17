#include<iostream>
#include<iomanip>
#define MAXN 10005
using namespace std;

int a[MAXN];
int n,k;

bool judge_num(int len){
    int cnt = 0;
    for(int i=1;i<=n;i++)
        cnt+=a[i]/len;
    return cnt>=k; //trueÔòºÏ·¨
}

int main(){
    double temp;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>temp;
        a[i] = temp*100;
    }
    int st=0,ed=1+1e7,mid;
    while(st+1<ed){
        mid = (st+ed)>>1;
        if(judge_num(mid)) st=mid;
        else ed=mid;
    }
    cout<<fixed<<setprecision(2)<<st*1.0/100;
    return 0;
}
