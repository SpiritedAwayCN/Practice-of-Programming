#include<stdio.h>
#define MAXK 55
int a[MAXK],b[MAXK],c[MAXK];
int main()
{
    int i,j;
    int n,k,p,pos,ans=0;
    scanf("%d%d%d",&n,&k,&p);
    for(i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(y<=p)
            pos=i;
        if(pos>=a[x])
            c[x]=b[x]; //c[x]在pos前的同色酒店个数，访问时更新
        a[x]=i;//当前颜色最后出现的位置
        ans=ans+c[x];
        b[x]++;//已获取到同色的酒店总数
    }
    printf("%d\n",ans);
    return 0;
}
