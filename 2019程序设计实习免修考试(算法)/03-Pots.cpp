#include<cstdio>
#include<queue>
#include<vector>
#define MAX_LIT 105
using namespace std;

bool vis[MAX_LIT][MAX_LIT];
int A,B,C;
struct node{
    int lit_A,lit_B;

    node *last;
    int init_type,arg_1,arg_2;
    node(int type = 0, int arg1 = 0, int arg2 = 0, int AA = 0,int BB = 0, node* las = NULL){
        last = las;
        init_type = type;
        arg_1 = arg1;
        arg_2 = arg2;
        if(type==0){
            //set_num
            lit_A=arg1;
            lit_B=arg2;
        }else if(type==1){
            //fill arg1
            if(arg1==1){
                lit_A=A; lit_B=BB;
                //printf("A=%d\n",A);
            }else{
                lit_A=AA; lit_B=B;
            }
        }else if(type==2){
            //drop arg1
            if(arg1==1){
                lit_A=0; lit_B=BB;
            }else{
                lit_A=AA; lit_B=0;
            }
        }else{
            //lit_A=AA;lit_B=BB;
            int& temp1 = (arg1==1?AA:BB);
            int& temp2 = (arg1==1?BB:AA);
            int& temp3 = (arg1==1?B:A);
            //printf("-%d %d\n",temp1,temp2);
            if(temp1+temp2<=temp3){
                temp2+=temp1;temp1=0;
            }else{
                temp1-=temp3-temp2;temp2=temp3;
            }
            lit_A = (arg1==1?temp1:temp2);
            lit_B = (arg1==1?temp2:temp1);
            //printf("lit_A,B=%d,%d\n",lit_A,lit_B);
        }
    }
};
queue<node*> srh;
vector<node*> solution;
node* cur;
bool insert_queue(node* next){
    //printf("push: A=%d B=%d\n",next->lit_A,next->lit_B);
    next->last = cur;
    if(vis[next->lit_A][next->lit_B]){
        delete next;
        return false;
    }
    vis[next->lit_A][next->lit_B] = true;
    //printf("push: A=%d B=%d\n",next->lit_A,next->lit_B);
    srh.push(next);
    if(next->lit_A==C || next->lit_B==C) {cur=next;return true;}
    return false;
}
int main(){
    scanf("%d%d%d",&A,&B,&C);
    //11 vis[0][0]=true;
    node* next = new node(0,0,0);
    if(insert_queue(next)){
        printf("0\n");
        return 0;
    }

    while(!srh.empty()){
        cur = srh.front();
       // printf("pop: A=%d,B=%d\n",cur->lit_A,cur->lit_B);
        srh.pop();
        next = new node(1,1,0,cur->lit_A,cur->lit_B);
        if(insert_queue(next)) break;
        next = new node(1,2,0,cur->lit_A,cur->lit_B);
        if(insert_queue(next)) break;
        next = new node(2,1,0,cur->lit_A,cur->lit_B);
        if(insert_queue(next)) break;
        next = new node(2,2,0,cur->lit_A,cur->lit_B);
        if(insert_queue(next)) break;
        next = new node(3,2,1,cur->lit_A,cur->lit_B);
        if(insert_queue(next)) break;
        next = new node(3,1,2,cur->lit_A,cur->lit_B);
        if(insert_queue(next)) break;
    }
    int step = 0;
    while(cur){
        solution.push_back(cur);
        cur = cur->last;
        step++;
    }
    if(srh.empty())
        printf("impossible");
    else{
        printf("%d\n",step-1);
        for(int i=step - 1;i>=0;i--){
            if(solution[i]->init_type == 0) continue;
            else if(solution[i]->init_type == 1){
                printf("FILL(%d)\n",solution[i]->arg_1);
            }else if(solution[i]->init_type == 2){
                printf("DROP(%d)\n",solution[i]->arg_1);
            }else{
                printf("POUR(%d,%d)\n",solution[i]->arg_1,solution[i]->arg_2);
            }
        }
    }
}
