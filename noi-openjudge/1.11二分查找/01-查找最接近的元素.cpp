#include<cstdio>
#define MAXN 100005
int a[MAXN],n,m;
int find_closest(int key){
    int s=1,e=n,mid;
    while(s<e){
        mid=(s+e+1)>>1;
        if(a[mid]==key) return key;
        if(a[mid]>key) e=mid-1;
        else s=mid;
    }
    return (s<n && key-a[s] > a[s+1]-key)? a[s+1] : a[s];
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    int key;
    while(m--){
        scanf("%d",&key);
        printf("%d\n",find_closest(key));
    }
    return 0;
}
