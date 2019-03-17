#include<iostream>
#define ll long long
using namespace std;

long long s,minc=1000000000000;
int l[10005],t[10005],w[10005],h[10005],n;
long long square(int k){//划出x=k这条直线，小矩形在直线左边的面积
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(l[i]+w[i]<=k) ans+=(ll)w[i]*h[i];
        else if( l[i]<k ) ans+=(ll)(k-l[i])*h[i];
    }
    return ans;
}

int main(){
    int r; cin>>r>>n;
    for(int i=1;i<=n;i++) {
        cin>>l[i]>>t[i]>>w[i]>>h[i];
        s+=(ll)w[i]*h[i];
    }

    int start=0,end=r,mid,ans;
    while(end>=start){
        mid = (start+end)/2;
        long long sq=square(mid);
        //cout<<start<<" "<<mid<<" "<<end<<" "<<sq<<endl;
        //小矩形在直线左边的面积随着直线向右平移逐渐减小
        if( sq>=s-sq){
            minc=sq*2-s;
            end=mid-1;
        }
        else start=mid+1;
    }

    start=0,end=r;
    while(end>=start){
        mid = (start+end)/2;
        long long sq=square(mid),cha=sq*2-s;
        //cout<<start<<" "<<mid<<" "<<end<<" "<<sq<<endl;
        if( sq>=s-sq ){//直线左边小矩形面积大于右边的
            if(cha>minc) end=mid-1;
            else ans=mid,start=mid+1;
        }
        else start=mid+1;
    }

    //cout<<minc<<endl;
    cout<<ans;

    return 0;
}
