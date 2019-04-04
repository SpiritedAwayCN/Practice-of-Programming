#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
// 继承写法
template<class T1, class T2, class T3 = greater<T1> >
class MyMultimap : public multimap<T1, T2, T3> {
public:
	void Set(T1 arg1, T2 arg2) {
		auto range = this->equal_range(arg1);
		for (auto it = range.first; it != range.second; it++)
			it->second = arg2;
	}
};

template <typename T1, typename T2>
ostream& operator <<(ostream& os, pair<T1, T2> p) {
	os << '(' << p.first << ',' << p.second << ')';
	return os;
}
/*
//正常写法
template<class T1, class T2, class T3 = greater<T1> >
class MyMultimap {
public:
	typedef typename multimap<T1, T2, T3>::iterator iterator;
	void insert(const pair<T1, T2>& pairs) {
		mymap.insert(pairs);
	}
	iterator begin(){
		return mymap.begin();
	}
	iterator end() {
		return mymap.end();
	}
	iterator find(T1 arg1) {
		return mymap.find(arg1);
	}
	void Set(const T1& first, const T2& second) {
		auto range = mymap.equal_range(first);
		for (auto i = range.first; i != range.second; ++i)
		{
			i->second = second;
		}
	}
	void clear() {
		mymap.clear();
	}

private:
	multimap<T1, T2, T3> mymap;
};
*/
struct Student
{
	string name;
	int score;
};
template <class T>
void Print(T first, T last) {
	for (; first != last; ++first)
		cout << *first << ",";
	cout << endl;
}
int main()
{

	Student s[] = { {"Tom",80},{"Jack",70},
					{"Jone",90},{"Tom",70},{"Alice",100} };

	MyMultimap<string, int> mp;
	for (int i = 0; i < 5; ++i)
		mp.insert(make_pair(s[i].name, s[i].score));
	Print(mp.begin(), mp.end()); //按姓名从大到小输出

	mp.Set("Tom", 78); //把所有名为"Tom"的学生的成绩都设置为78
	Print(mp.begin(), mp.end());



	MyMultimap<int, string, less<int> > mp2;
	for (int i = 0; i < 5; ++i)
		mp2.insert(make_pair(s[i].score, s[i].name));

	Print(mp2.begin(), mp2.end()); //按成绩从小到大输出
	mp2.Set(70, "Error");          //把所有成绩为70的学生，名字都改为"Error"
	Print(mp2.begin(), mp2.end());
	cout << "******" << endl;

	mp.clear();

	string name;
	string cmd;
	int score;
	while (cin >> cmd) {
		if (cmd == "A") {
			cin >> name >> score;
			if (mp.find(name) != mp.end()) {
				cout << "erroe" << endl;
			}
			mp.insert(make_pair(name, score));
		}
		else if (cmd == "Q") {
			cin >> name;
			MyMultimap<string, int>::iterator p = mp.find(name);
			if (p != mp.end()) {
				cout << p->second << endl;
			}
			else {
				cout << "Not Found" << endl;
			}
		}
	}
	return 0;
}