#include<iostream>
#include<cstdlib>
#include<vector>

constexpr double fix_err = 1e-3;
using namespace std;
class instruction{
public:
    instruction(double arg1,double arg2,int ope,double arg3)
    : num1(arg1)
    , num2(arg2)
    , oper_type(ope)
    , ans(arg3){}
    friend ostream& operator<<(ostream &ost,instruction& A){
        ost<<A.num1<<' ';
        switch(A.oper_type){
        case 0:
            ost<<'+';
            break;
        case 1:
            ost<<'-';
            break;
        case 2:
            ost<<'*';
            break;
        case 3:
            ost<<'/';
        }
        ost<<' '<<A.num2<<" = "<<A.ans<<endl;
        return ost;
    }
private:
    double num1,num2,ans;
    int oper_type;
};
vector<double> table;
vector<double> calc;
vector<instruction> solution;
int n;
bool judge_finished(double num){
    if(num<=0+fix_err) return false;
    while(num<100) num*=10;
    while(num>1000) num/=10;
    return (int)num == 314;
}
inline bool judge_equal(double d1,double d2){
    return d1-d2<=fix_err && d1-d2>=-fix_err;
}

bool dfs(int num){

    if(num==1){
        for(int i=0;i<n;i++){
            if(judge_equal(calc[i],0)) continue;
            if(judge_finished(calc[i])){
                return true;
            }else{
                return false;
            }
        }
        return false;
    }
    for(int i=0;i<n;i++){
        if(judge_equal(calc[i],0)) continue;
        for(int j=0;j<n;j++){

            if(i==j||judge_equal(calc[j],0)) continue;
            double rec1=calc[i],rec2=calc[j];

            for(int law=0;law<4;law++){
                calc[i]=0;
                if(law==0) calc[j]=rec1+rec2;
                else if(law==1 && rec1<rec2)continue;
                else if(law==1) calc[j]=rec1-rec2;
                else if(law==2) calc[j]=rec1*rec2;
                else calc[j]=rec1/rec2;
                solution.push_back(instruction(rec1,rec2,law,calc[j]));
                if(dfs(num-1)) return true;
                solution.pop_back();
                calc[i]=rec1;
                calc[j]=rec2;
            }
        }

    }
    return false;
}
void initialize(){
    calc.clear();
    solution.clear();
    for(int i=0;i<n;i++)
        calc.push_back(table[i]);
}
int main(){
    cout<<"Please input all the integers you have,\nand the program will find the solution to get 314.\n";
    cout<<"\n\n#NOTE:# Please input an integer 0 at the end of your input.\n";
    double temp;
    cin>>temp;
    while(temp){
        table.push_back(temp);
        cin>>temp;
    }
    n = table.size();
    initialize();
    if(dfs(n)){
        for(int i=0;i<solution.size();i++)
            cout<<solution[i];
    }else{
        cout<<"No solution! Here are all the feasible numbers needed:"<<endl;
        table.push_back(0);
        n++;
        for(int i=1;i<=9;i++){
            table[n-1]=i;
            initialize();
            if(dfs(n)){
                cout<<"\n=====NUMBER "<<i<<" is feasible:=====\n";
                for(int j=0;j<solution.size();j++)
                    cout<<solution[j];
            }
        }
        cout<<"\n==============================\n";
        cout<<"All the feasible numbers are listed above. If there is no any input, please try to get more numbers.\n";
    }
    system("pause");
    return 0;
}
