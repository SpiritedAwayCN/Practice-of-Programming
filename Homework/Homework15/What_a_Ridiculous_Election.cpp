#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int ten[]={1,10,100,1000,10000,100000};
int ans[1000000];
short vis[1000000];
struct node{
    int number;
    int status;
    bool swp(int index1, int index2){
        if(index1==index2) return false;
        short bit = (number/ten[index1])%10 - (number/ten[index2])%10;
        number -= bit*ten[index1];
        number += bit*ten[index2];
        return true;
    }
    bool inc(int index){
        if((status&3)>=3) return false;
        short bit = (number/ten[index])%10;
        number -= bit*ten[index];
        bit+=1; bit%=10;
        number += bit*ten[index];
        status+=1;
        return true;
    }
    bool dob(int index){
        if(((status>>2)&3)>=2) return false;
        short bit = (number/ten[index])%10;
        number -= bit*ten[index];
        bit*=2; bit%=10;
        number += bit*ten[index];
        status+=1<<2;
        return true;
    }
};
queue<node> BFS_queue;

inline void push_queue(node& current){
    if(vis[current.number] & (1<<(current.status&15))) return;
    current.status+=1<<4;
    if(ans[current.number]<0)
        ans[current.number]=current.status>>4;
    vis[current.number] |= 1<<(current.status&15);
    BFS_queue.push(current);
    return;
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    memset(ans,-1,sizeof(ans));
    BFS_queue.push(node{12345,0});
    vis[12345]=1;
    ans[12345]=0;
    while(!BFS_queue.empty()){
        node current = BFS_queue.front();
        BFS_queue.pop();
        node tmp = current;
        for(int i=0;i<4;i++){
            tmp=current;
            if(tmp.swp(i,i+1))
                push_queue(tmp);
        }
        for(int i=0;i<5;i++){
            tmp=current;
            if(tmp.inc(i))
                push_queue(tmp);
            tmp=current;
            if(tmp.dob(i))
                push_queue(tmp);
        }   
    }
    int n;
    while(scanf("%d",&n)!=EOF)
        printf("%d\n",ans[n]);
    return 0;
}
