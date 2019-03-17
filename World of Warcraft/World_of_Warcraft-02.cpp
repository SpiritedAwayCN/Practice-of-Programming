#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<list>
#include<sstream>
//#include<cstdio>
#define MAX_TYPE 5
#define OUTPUT_HOUR_ONLY true


using namespace std;
int init_hp[MAX_TYPE];
class GameTimer{
friend GameTimer& operator++(GameTimer& gt){
    gt.add_time(1);
    return gt;
}
friend ostream& operator<<(ostream& ost ,GameTimer& gt){
    ost<<setw(3)<<setfill('0')<<gt.hour;
    if(!OUTPUT_HOUR_ONLY)
        ost<<':'<<setw(2)<<setfill('0')<<gt.minute;
    return ost;
}
public:
    GameTimer():hour(0),minute(0){}
    void add_time(int mini){
        minute+=mini;
        check_feasible();
    }
    void set_time(int h,int m){
        hour = h;
        minute = m;
        check_feasible();
    }
    int get_hour() const {return hour;}
    int get_minute() const {return minute;}
private:
    void check_feasible(){
        hour+=minute/60;
        minute%=60;
    }
    int hour;
    int minute;
};
GameTimer* game_timer;

class Weapon{
public:
    virtual string get_type_name() const = 0;
    virtual int get_type_id() const = 0;
    int get_atk() const {return atk;}
    void set_atk(int num) {atk = num;}
    void add_atk(int num) {atk += num;}
protected:
    Weapon(int natk)
//    : uid(id)
    {
    }
private:
//9    int uid;
    int atk;
};
class sword : public Weapon{
public:
    sword(int natk = 0)
    : Weapon(natk)
    {
    }
    string get_type_name() const {return "sword";}
    int get_type_id() const {return 0;}
};
class bomb : public Weapon{
public:
    bomb(int natk = 0)
    : Weapon(natk)
    {
    }
    string get_type_name() const {return "bomb";}
    int get_type_id() const {return 1;}
};
class arrow : public Weapon{
public:
    arrow(int natk = 0)
    : Weapon(natk)
    {
    }
    string get_type_name() const {return "arrow";}
    int get_type_id() const {return 2;}
};

class soldier{
public:
    void set_hp(int num){hp=num;}
    void set_atk(int num){atk=num;}
    int get_uid() const{return uid;}
    int get_hp() const{return hp;}
    int get_atk() const{return atk;}
    virtual string get_type() const = 0;
    int get_max_weap() const {return max_weap;}
    Weapon* get_weapon(int index) const{
        if(index<0 || index >= equipped_weapon.size()) return NULL;
        return equipped_weapon[index];
    }
    bool gain_weapon(int type_id){
        if(equipped_weapon.size()>=max_weap) return false;
        Weapon* new_weapon;
        switch(type_id){
        case 0:
            new_weapon = new sword();
            break;
        case 1:
            new_weapon = new bomb();
            break;
        case 2:
            new_weapon = new arrow();
            break;
        }
        equipped_weapon.push_back(new_weapon);
        return true;
    }
    virtual ~soldier(){
        for(int i=0;i<equipped_weapon.size();i++)
            delete equipped_weapon[i];
    }
protected:
    soldier(int id,int nhp,int natk,int mw)
    : uid(id)
    , hp(nhp)
    , atk(natk)
    , max_weap(mw)
    {
    }
private:
    vector<Weapon*> equipped_weapon;
    int uid;
    int hp;
    int atk;
    int max_weap;
};
class dragon : public soldier{
public:
    dragon(int id,int hp_mon,int nhp = init_hp[0],int natk = 0)
    : soldier(id,nhp,natk,1)
    , morale(hp_mon*1.0/nhp - 1)
    {
        gain_weapon(get_uid()%3);
    }
    string get_type() const{return "dragon";}
    double get_morale() const {return morale;}
private:
    double morale;
};
class ninja : public soldier{
public:
    ninja(int id,int hp_mon,int nhp = init_hp[1],int natk = 0)
    : soldier(id,nhp,natk,2)
    {
        gain_weapon(get_uid()%3);
        gain_weapon((get_uid()+1)%3);
    }
    string get_type() const{return "ninja";}
};
class iceman : public soldier{
public:
    iceman(int id,int hp_mon,int nhp = init_hp[2],int natk = 0)
    : soldier(id,nhp,natk,1)
    {
        gain_weapon(get_uid()%3);
    }
    string get_type() const{return "iceman";}
};
class lion : public soldier{
public:
    lion(int id,int hp_mon,int nhp = init_hp[3],int natk = 0)
    : soldier(id,nhp,natk,0)
    , loyalty(hp_mon - nhp)
    {
    }
    string get_type() const{return "lion";}
    int get_loyalty() const{return loyalty;}
private:
    int loyalty;
};
class wolf : public soldier{
public:
    wolf(int id,int nhp = init_hp[4],int natk = 0)
    : soldier(id,nhp,natk,0)
    {
    }
    string get_type() const{return "wolf";}
};

class commander{
public:
    bool create_soldier(){
        stringstream sst("");
        int type_id = get_next_feasible_type_id();
        if(type_id < 0) return false;//create failed
        soldier* new_soldier;
        add_total_soldier();
        ++soldier_num[type_id];
        switch(type_id){
        case 0:
            new_soldier = new dragon(get_total_soldier(),get_hp_money());
            sst << "It has a "<<new_soldier->get_weapon(0)->get_type_name();
            sst.setf(ios::fixed);
            sst << ",and it's morale is " << setprecision(2) << ((dragon*)new_soldier)->get_morale()<<'\n';
            break;
        case 1:
            new_soldier = new ninja(get_total_soldier(),get_hp_money());
            sst << "It has a "<<new_soldier->get_weapon(0)->get_type_name();
            sst << " and a " <<new_soldier->get_weapon(1)->get_type_name()<<'\n';
            break;
        case 2:
            new_soldier = new iceman(get_total_soldier(),get_hp_money());
            sst << "It has a "<<new_soldier->get_weapon(0)->get_type_name()<<'\n';
            break;
        case 3:
            new_soldier = new lion(get_total_soldier(),get_hp_money());
            sst << "It's loyalty is " << ((lion*)new_soldier)->get_loyalty()<<'\n';
            break;
        case 4:
            new_soldier = new wolf(get_total_soldier());
            break;
        }
        add_hp_money(- new_soldier->get_hp());
        soldier_list.push_back(new_soldier);
        cout<< *game_timer <<' ' << get_team_color() << ' ' << new_soldier->get_type() << ' ' << new_soldier->get_uid();
        cout<< " born with strength " << new_soldier->get_hp() << ',' << get_soldier_num(type_id) << ' ' << new_soldier->get_type();
        cout<< " in " << get_team_color() << " headquarter"<<endl;
        cout<< sst.str();
        last_create_id = type_id;
        return true;
    }
    int get_next_feasible_type_id() {
        int temp = next_type_id(last_create_id),cnt = 0;
        while(init_hp[temp]>hp_money){
            temp = next_type_id(temp);
            cnt++;
            if(cnt==MAX_TYPE) return -1;
        }
        return temp;
    };
    virtual int next_type_id(int index) = 0;
    int get_hp_money() const{return hp_money;}
    void set_hp_money(int num){hp_money=num;}
    void add_hp_money(int num){hp_money+=num;}
    int get_total_soldier() const{return total_soldier;}
    int get_soldier_num(int type_id) const{return soldier_num[type_id];}
    int get_sum_soildier_num() const{
        int sum=0;
        for(int i=0;i<MAX_TYPE;i++)
            sum+=soldier_num[i];
        return sum;
    }
    void add_total_soldier(int num = 1) {total_soldier+=num;}
    virtual ~commander(){
        //cout<<"~commander()"<<endl;
        for(list<soldier*>::iterator iter = soldier_list.begin();iter!=soldier_list.end();iter++){
            delete *iter;
        }
        soldier_list.clear();
    }
protected:
    commander(int hp_mon, int zero_type)
    : hp_money(hp_mon)
    , last_create_id(zero_type)
    , total_soldier(0)
    {
        for(int i=0;i<MAX_TYPE;i++)
            soldier_num[i] = 0;
    }
private:
    virtual string get_team_color() const = 0;
    int hp_money;
    int last_create_id;
    int total_soldier;
    int soldier_num[MAX_TYPE];
    list<soldier*> soldier_list;
};
class RedTeam : public commander{
public:
    RedTeam(int hp_mon,int zero_type = 0)
    : commander(hp_mon, zero_type)
    {
    }
    string get_team_color() const{return "red";}
    int next_type_id(int index){
        //iceman¡¢lion¡¢wolf¡¢ninja¡¢dragon
        //0->dragon 1->ninja 2->iceman 3->lion 4->wolf
        static int create_order[MAX_TYPE]={2, 0, 3, 4, 1};
        return create_order[index];
    }
};
class BlueTeam : public commander{
public:
    BlueTeam(int hp_mon,int zero_type = 4)
    : commander(hp_mon, zero_type)
    {
    }
    string get_team_color() const{return "blue";}
    int next_type_id(int index){
        //lion¡¢dragon¡¢ninja¡¢iceman¡¢wolf
        //0->dragon 1->ninja 2->iceman 3->lion 4->wolf
        static int create_order[MAX_TYPE]={1, 2, 4, 0, 3};
        return create_order[index];
    }
};

RedTeam* red_team;
BlueTeam* blue_team;

void Game_Run(){
    //GameTimer& current_time = *game_timer;
    bool red_finished = false, blue_finished = false;
    while(true){
        // The main loop
        switch(game_timer->get_minute()){
        case 0:
            {
                if(red_finished == false && !red_team->create_soldier()){
                    cout << *game_timer << " red headquarter stops making warriors"<<endl;
                    red_finished = true;
                }
                if(blue_finished == false && !blue_team->create_soldier()){
                    cout << *game_timer << " blue headquarter stops making warriors"<<endl;
                    blue_finished = true;
                }
            }

        }
        if(red_finished && blue_finished) break;
        game_timer->add_time(60);
    }
}

int main(){
    int T,M;
    cin>>T;
    for(int ii=1;ii<=T;ii++){
        cin>>M;
        for(int i=0;i<MAX_TYPE;i++)
            cin>>init_hp[i];
        game_timer = new GameTimer;
        red_team = new RedTeam(M);
        blue_team = new BlueTeam(M);

        cout<<"Case:"<<ii<<endl;
        Game_Run();

        delete red_team;
        delete blue_team;
        delete game_timer;
    }
    return 0;
}
