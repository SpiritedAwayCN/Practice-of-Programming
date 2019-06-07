#include<bits/stdc++.h>
using namespace std;
int minStp[100000][4][3];
string str;
struct Node {
    string s;   int op2, op3, stp;
    Node() {};
    Node(string _s, int _op2, int _op3, int _stp) {
        s = _s, op2 = _op2, op3 = _op3, stp = _stp;
    }
} p, q;
bool operator<(Node a, Node b) {
    return a.stp > b.stp;
}
int str2int(string s) {
    int ret = 0;
    for(int i=0;i<5;i++)
        ret *= 10,  ret += s[i]-'0';
    return ret;
}
void bfs()
{
    priority_queue<Node> que;
    que.push(Node("12345", 0, 0, 0));
    minStp[12345][0][0] = 0;
    int num;
    while(!que.empty())
    {
        p = que.top();
        que.pop();
        q.stp = p.stp + 1;
        for(int i=0;i<4;i++)
        {
            q.s = p.s;
            swap(q.s[i], q.s[i+1]);
            q.op2 = p.op2,  q.op3 = p.op3;
            num = str2int(q.s); 
            if(minStp[num][q.op2][q.op3] != 0x3f3f3f3f) continue;
            minStp[num][q.op2][q.op3] = q.stp;
            que.push(q);
        }   

        if(p.op2 < 3) {
            for(int i=0;i<5;i++)
            {
                q.s = p.s;
                q.s[i] = char(((q.s[i]-'0')+1)%10 + '0');
                q.op2 = p.op2+1,    q.op3 = p.op3;
                num = str2int(q.s);
                if(minStp[num][q.op2][q.op3] != 0x3f3f3f3f) continue;
                minStp[num][q.op2][q.op3] = q.stp;
                que.push(q);
            }
        }

        if(p.op3 < 2) {
            for(int i=0;i<5;i++)
            {
                q.s = p.s;
                q.s[i] = char(((q.s[i]-'0')*2)%10 + '0');
                q.op2 = p.op2,  q.op3 = p.op3+1;
                num = str2int(q.s);
                if(minStp[num][q.op2][q.op3] != 0x3f3f3f3f) continue;
                minStp[num][q.op2][q.op3] = q.stp;
                que.push(q);
            }
        }
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("out_std.txt","w",stdout);
    memset(minStp, 0x3f, sizeof(minStp));
    bfs();
    while(cin>>str)
    {
        int mn = 0x3f3f3f3f;
        for(int i=0;i<=3;i++)
        for(int j=0;j<=2;j++)
            mn = min(mn, minStp[str2int(str)][i][j]);

        printf("%d\n", mn==0x3f3f3f3f?-1:mn);
    }
}
