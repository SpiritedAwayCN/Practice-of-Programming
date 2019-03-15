//http://bailian.openjudge.cn/practice/2803/
#include<iostream>
#include<string>

using namespace std;
int goal,num,len;
string number;
int get_sum(int split){
    int sum=0,temp=0;
    for(int i=0;i<len;i++){
        temp*=10;
        temp+=number[i]-'0';
        if(split&(1<<i)){
            sum+=temp;
            temp=0;
        }
    }
    sum+=temp;
    return sum;
}
void print_sol(int split){
    for(int i=0;i<len;i++){
        cout<<number[i];
        if(split&(1<<i))
            cout<<' ';
    }

}
int main(){
    int sum,temp,ans,sol;
    while(true){
        cin>>goal>>num;
        if(goal==0 && num==0)break;
        number = to_string(num);
        len=number.length();
        sum=0;ans=0;sol=-1;
        for(int i=0;i<len;i++){
            sum+=number[i]-'0';
        }
        sum=1<<len-1;
        for(int i=0;i<sum;i++){
            temp=get_sum(i);
            if(temp<=goal && temp>ans){
                ans=temp;
                sol=i;
            }else if(temp==ans){
                sol=-2;
                //暂时设置为无解
            }
        }
        if(sol==-2){
            cout<<"rejected\n";
            continue;
        }else if(sol==-1){
            cout<<"error\n";
            continue;
        }
        cout<<ans<<' ';
        print_sol(sol);
        cout<<endl;
    }
    return 0;
}
