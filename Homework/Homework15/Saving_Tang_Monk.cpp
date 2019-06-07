#include<cstdio>
#include<cstring>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 105;
constexpr int MAXK = 10;
int Tmap[MAXN][MAXN], vis[MAXN][MAXN][MAXK],ans,n,k;
int cnts,tx,ty;
struct Coordinate{
    int x,y,key_num;
    int status,st;
    bool operator<(const Coordinate& B) const{
        return st>B.st;
    }
};
//郭炜的输入数据有行末空格，简直有毒！！！
priority_queue<Coordinate> BFS_queue;

inline bool push_queue(int x,int y,int key, int status, int step){
    if(x<1||y<1||x>n||y>n) return false;
    if(tx==x && ty==y && key>=k) {ans=step + 1; return true;}
    if(Tmap[x][y]==-10) return false;
    if(Tmap[x][y]==key+1) key++;
    step+=1;
    if(Tmap[x][y]<0 && status&(1<<-(Tmap[x][y]+1))){
        step+=1;
        status^=1<<-(Tmap[x][y]+1);
    }
    if(vis[x][y][key] & (1<<status)) return false;
    vis[x][y][key]|=1<<status;
    BFS_queue.push(Coordinate{x,y,key,status,step});
    return false;
}

int main(){
    char temp;
    int init_s;
    while(scanf("%d%d",&n,&k)!=EOF){
        if(n==0) break;
        memset(Tmap,0,sizeof(Tmap));
        memset(vis,0,sizeof(vis));
        cnts=ans=0;
        bool flag = false;
        while(!BFS_queue.empty()) BFS_queue.pop();
        int sx,sy;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>temp;
                switch (temp){
                case 'K':
                    sx=i;sy=j;
                    break;
                case 'S':
                    Tmap[i][j]=-(++cnts);
                    break;
                case 'T':
                    tx=i,ty=j;
                    break;
                case '#':
                    Tmap[i][j]=-10;
                    break;
                case '.':
                    break;
                default:
                    Tmap[i][j]=temp-'0';
                    break;
                }
            }
        }
        init_s=(1<<cnts)-1;
        BFS_queue.push(Coordinate{sx,sy,0,init_s,0});
        vis[sx][sy][0]=1<<init_s;

        while(!BFS_queue.empty()){
            Coordinate current = BFS_queue.top();
            BFS_queue.pop();
            flag|=push_queue(current.x-1,current.y,current.key_num,current.status,current.st);
            if(flag) break;
            flag|=push_queue(current.x+1,current.y,current.key_num,current.status,current.st);
            if(flag) break;
            flag|=push_queue(current.x,current.y-1,current.key_num,current.status,current.st);
            if(flag) break;
            flag|=push_queue(current.x,current.y+1,current.key_num,current.status,current.st);
            if(flag) break;
        }
        if(flag)
            printf("%d\n",ans);
        else{
            printf("impossible\n");
        }
            
    }
    return 0;
}