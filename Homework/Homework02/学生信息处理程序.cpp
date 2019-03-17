#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
// 在此处补充你的代码
public:
	void input(){
		char c;
		c=cin.get();
		stringstream sst;
		while(c!=','){
			sst<<c;
			c=cin.get();
		}
		name = sst.str();
		cin>>age;
		do{
			c=cin.get();
		}while(c!=',');
		cin>>id;
		for(int i=0;i<4;i++){
			do{
				c=cin.get();
			}while(c!=',');
			cin>>score[i];
		}
	} 
	void calculate(){
		aver = 0;
		for(int i=0;i<4;i++)
			aver = (aver*i + score[i])/(i+1);			
	}
	void output(){
		cout<<name<<','<<age<<','<<id<<','<<aver;
	}
private:
	string name;
	int age;
	int id;
	int score[4];
	double aver;	
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}
