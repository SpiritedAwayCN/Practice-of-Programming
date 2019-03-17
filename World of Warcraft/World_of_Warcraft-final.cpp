#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<list>
#include<sstream>
#include<queue>

//#include<fstream>

#define MAX_TYPE 5
#define MAX_WEAPON 10
#define MAX_ENEMY_NUM 2
#define OUTPUT_HOUR_ONLY false

//#define cout ost
//#define cin ist

using namespace std;
//ifstream ist("input-4.txt");
//ofstream ost("my_output.txt");
int init_hp[MAX_TYPE];
int init_atk[MAX_TYPE];
int M,N,R,K,T;

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
    void set_minite(int mini){minute = mini;}
    int get_hour() const {return hour;}
    int get_minute() const {return minute;}
    int get_t_minute() const {return hour*60+minute;}
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
//    virtual bool use_weapon(soldier* user, soldier* target) const = 0;
    int get_atk_rate() const {return atk_rate;}
    void set_atk_rate(int num) {atk_rate = num;}
//    void add_atk(int num) {atk += num;}
protected:
    Weapon(int natk)
    : atk_rate(natk)
    {
    }
private:
//9    int uid;
    int atk_rate; //will be divided 10 when calculating
};
class sword : public Weapon{
public:
    sword(int natk = 2)
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
    arrow(int natk = 3)
    : Weapon(natk)
    , remain(3)
    {
    }
    string get_type_name() const {return "arrow";}
    int get_type_id() const {return 2;}
    int get_remain() const {return remain;}
    int use_arrow() {remain--;};
private:
    int remain;
};

class soldier;

class City{
public:
    City(int id)
    : city_id(id)
    , flag_type(id&1)
    , element(0)
    , last_winner(0)
    , red_soldier(NULL)
    , blue_soldier(NULL)
    , battle_stauts(false)
    {
    }
    //soldiers will be destructed in ~command()
    soldier* red_soldier;
    soldier* blue_soldier;
    void do_escape();
    void do_report_weapon(bool red);
    void create_element(){
        //20min
        element += 10;
    }
    void do_gain_element();
    //被箭射死时，只有城市中双方均有武士才不会被清除
    void do_shoot();
    void do_clear_shot();
    void do_battle();
    void do_balance_01();
    void do_balance_02(bool red);
    void do_balance_03();
    stringstream& get_sst(){return sst;}
private:
    bool battle_stauts;
    int city_id;
    int element;
    int flag_type;//0 1没有 2蓝先 3红先
    int last_winner;//0初始 2蓝 3红
    stringstream sst;
};
vector<City*> city;

class soldier{
public:
    friend void City::do_battle();
    friend void City::do_shoot();
    bool arrive_tag;
    void add_hp(int num){hp+=num;}
    void set_atk(int num){atk=num;}
    int get_uid() const{return uid;}
    int get_hp() const{return hp;}
    int get_atk() const{return atk;}
    string get_team_name() const {return team_name;}
    virtual string get_type() const = 0;
    void lose_weapon(int type_id){
        switch(type_id){
        case 0:
            if(!sword_ptr) return;
            delete sword_ptr;
            sword_ptr = NULL;
            break;
        case 1:
            if(!bomb_ptr) return;
            delete bomb_ptr;
            bomb_ptr = NULL;
            break;
        case 2:
            if(!arrow_ptr) return;
            delete arrow_ptr;
            arrow_ptr = NULL;
            break;
        }
    }
    void die();

    bool gain_weapon(int type_id){
        int temp = atk*2/10;
        switch(type_id){
        case 0:
            if(sword_ptr || temp<=0) return false;
            sword_ptr = new sword(temp);
            break;
        case 1:
            bomb_ptr = new bomb();
            break;
        case 2:
            arrow_ptr = new arrow(R);
            break;
        }
        return true;
    }
    bool gain_weapon(Weapon* Wep){
        if(!Wep) return false;
        switch(Wep->get_type_id()){
        case 0:
            if(sword_ptr) return false;
            sword_ptr = (sword*)Wep;
            break;
        case 1:
            if(bomb_ptr) return false;
            bomb_ptr = (bomb*)Wep;
            break;
        case 2:
            if(arrow_ptr) return false;
            arrow_ptr = (arrow*)Wep;
            break;
        }
        return true;
    }
    void move_next();
    void report_weapons(){
        cout << *game_timer<<' '<<get_team_name()<<' '<<get_type()<<' '<<get_uid()<<" has ";
        int sum=0;
        if(arrow_ptr){
            sum++;
            cout<<"arrow("<<arrow_ptr->get_remain()<<')';
        }
        if(bomb_ptr){
            sum++;
            if(arrow_ptr) cout<<',';
            cout<<"bomb";
        }
        if(sword_ptr){
            sum++;
            if(arrow_ptr || bomb_ptr) cout<<',';
            cout<<"sword("<<sword_ptr->get_atk_rate()<<')';
        }
        if(!sum){cout<<"no weapon";}
        cout<<endl;
    }
    void being_stolen_weapon(soldier* source){
        if(source->gain_weapon(arrow_ptr)){
            arrow_ptr = NULL;
        }
        if(source->gain_weapon(bomb_ptr)){
            bomb_ptr = NULL;
        }
        if(source->gain_weapon(sword_ptr)){
            sword_ptr = NULL;
        }
    }
    void attack_other(soldier* target, bool rev = false){
        //直接打，打完了看死的有没有炸弹
        int temp = atk;
        if(rev) temp /= 2;
        game_timer->set_minite(40);
        stringstream& sst = city[city_id]->get_sst();
        if(rev){
            sst<<*game_timer<<' '<<*this<<" fought back against "<<*target<<" in city "<<city_id<<endl;
        }else{
            sst<<*game_timer<<' '<<*this<<" attacked "<<*target<<" in city "<<city_id;
            sst<<" with "<<hp<<" elements and force "<<atk<<endl;
        }
        game_timer->set_minite(38);
        if(sword_ptr){
            temp += sword_ptr->get_atk_rate();
            sword_ptr->set_atk_rate(sword_ptr->get_atk_rate()*8/10);
            if(sword_ptr->get_atk_rate()<=0){
                delete sword_ptr;
                sword_ptr = NULL;
            }
        }
        target->hp-=temp;
        if(target->hp <=0)return;
        //反击，死了则不反击
        if(target->get_type()!="ninja" && !rev) target->attack_other(this,true);
    }
    virtual ~soldier(){
        delete sword_ptr;
        delete bomb_ptr;
        delete arrow_ptr;
    }
    friend ostream& operator<<(ostream& ost, soldier& sd){
        ost<<sd.get_team_name()<<' '<<sd.get_type()<<' '<<sd.get_uid();
        return ost;
    }
protected:
    soldier(const string& team,int id,int nhp,int natk)
    : uid(id)
    , hp(nhp)
    , atk(natk)
    , team_name(team)
    , sword_ptr(NULL)
    , bomb_ptr(NULL)
    , arrow_ptr(NULL)
    , arrive_tag(false)
    {
        if(team == "red") city_id = 0;
        else city_id = N+1;
    }
    int city_id;
private:
    sword* sword_ptr;
    bomb* bomb_ptr;
    arrow* arrow_ptr;

    //priority_queue<Weapon*, vector<Weapon*>, prepare_comp> prepare_queue;
    int uid;
    int hp;
    int atk;
    string team_name;
};
class dragon : public soldier{
public:
    dragon(const string& team,int id,int hp_mon,int nhp = init_hp[0],int natk = init_atk[0])
    : soldier(team,id,nhp,natk)
    , morale(hp_mon*1.0/nhp - 1)
    {
        gain_weapon(get_uid()%3);
    }
    string get_type() const{return "dragon";}
    double get_morale() const {return morale;}
    void add_morale(double num) {morale += num;}
private:
    double morale;
};
class ninja : public soldier{
public:
    ninja(const string& team,int id,int hp_mon,int nhp = init_hp[1],int natk = init_atk[1])
    : soldier(team,id,nhp,natk)
    {
        gain_weapon(get_uid()%3);
        gain_weapon((get_uid()+1)%3);
    }
    string get_type() const{return "ninja";}
};
class iceman : public soldier{
public:
    iceman(const string& team,int id,int hp_mon,int nhp = init_hp[2],int natk = init_atk[2])
    : soldier(team,id,nhp,natk)
    , step_cont(0)
    {
        gain_weapon(get_uid()%3);
    }
    string get_type() const{return "iceman";}
    int step_cont;
};
class lion : public soldier{
public:
    lion(const string& team,int id,int hp_mon,int nhp = init_hp[3],int natk = init_atk[3])
    : soldier(team,id,nhp,natk)
    , loyalty(hp_mon - nhp)
    , last_hp(nhp)
    {
    }
    string get_type() const{return "lion";}
    int get_loyalty() const{return loyalty;}
    int get_last_hp() const{return last_hp;}
    void set_last_hp(int num) {last_hp = num;}
    void add_loyalty(int num) {loyalty+=num;}
    void check_escape();
private:
    int loyalty;
    int last_hp;
};
class wolf : public soldier{
public:
    wolf(const string& team,int id,int nhp = init_hp[4],int natk = init_atk[4])
    : soldier(team,id,nhp,natk)
    {
    }
    string get_type() const{return "wolf";}
};


class commander{
public:
    bool create_soldier(){
        int type_id = get_next_feasible_type_id();
        if(type_id < 0) return false;//create failed
        stringstream sst("");
        soldier* new_soldier;
        add_total_soldier();
        ++soldier_num[type_id];
        switch(type_id){
        case 0:
            new_soldier = new dragon(get_team_color(),get_total_soldier(),get_hp_money());
            sst.setf(ios::fixed);
            sst << "Its morale is " << setprecision(2) << ((dragon*)new_soldier)->get_morale()<<'\n';
            break;
        case 1:
            new_soldier = new ninja(get_team_color(),get_total_soldier(),get_hp_money());
            break;
        case 2:
            new_soldier = new iceman(get_team_color(),get_total_soldier(),get_hp_money());
            break;
        case 3:
            new_soldier = new lion(get_team_color(),get_total_soldier(),get_hp_money());
            sst << "Its loyalty is " << ((lion*)new_soldier)->get_loyalty()<<'\n';
            break;
        case 4:
            new_soldier = new wolf(get_team_color(),get_total_soldier());
            break;
        }
        add_hp_money(- new_soldier->get_hp());
        soldier_list.push_back(new_soldier);
        cout<< *game_timer <<' ' << get_team_color() << ' ' << new_soldier->get_type() << ' ' << new_soldier->get_uid()<< " born"<<endl;
        cout<<sst.str();
        last_create_id = type_id;
        if(get_team_color()=="red"){
            city[0]->red_soldier=new_soldier;
        }else{
            city[N+1]->blue_soldier=new_soldier;
        }
        return true;
    }
    int get_next_feasible_type_id() {
        int temp = next_type_id(last_create_id),cnt = 0;
        //不够就直接停
        return init_hp[temp]>hp_money? -1 : temp;
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
    void delete_soldier(soldier* ptr){
        soldier_list.remove(ptr);
    }
    void do_move(){
        for(list<soldier*>::iterator iter = soldier_list.begin();iter!=soldier_list.end();iter++){
            //cout<<"here\n";
            (*iter)->move_next();
        }
    }
    void add_enemy_num(){enemy_num++;}
    int get_enemy_num() const {return enemy_num;}
    void report_elements(){
        cout << *game_timer<<' '<<hp_money<<" elements in "<<get_team_color()<<" headquarter"<<endl;
    }
    virtual ~commander(){;
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
    , enemy_num(0)
    {
        for(int i=0;i<MAX_TYPE;i++)
            soldier_num[i] = 0;
    }
private:
    virtual string get_team_color() const = 0;
    int enemy_num;
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
        //0->dragon 1->ninja 2->iceman 3->lion 4->wolf
        static int create_order[MAX_TYPE]={1, 2, 4, 0, 3};
        return create_order[index];
    }
};

RedTeam* red_team;
BlueTeam* blue_team;

void City::do_escape(){
    if(red_soldier && red_soldier->get_type() == "lion")
        ((lion*)red_soldier)->check_escape();
    if(blue_soldier && blue_soldier->get_type() == "lion")
        ((lion*)blue_soldier)->check_escape();
}
void City::do_report_weapon(bool red){
    if(red && red_soldier) red_soldier->report_weapons();
    if(red == false && blue_soldier) blue_soldier->report_weapons();
}
void City::do_gain_element(){
    //30min
    if(red_soldier && blue_soldier){
        battle_stauts = true;
        return;
    }
    if(red_soldier){
        red_team->add_hp_money(element);
        cout<<*game_timer<<' '<<*red_soldier<<" earned "<<element<<" elements for his headquarter"<<endl;
        element = 0;
    }
    if(blue_soldier){
        blue_team->add_hp_money(element);
        cout<<*game_timer<<' '<<*blue_soldier<<" earned "<<element<<" elements for his headquarter"<<endl;
        element = 0;
    }
}
void City::do_shoot(){
    if(red_soldier && red_soldier->arrow_ptr && city_id != N){
        if(city[city_id+1]->blue_soldier){
            city[city_id+1]->blue_soldier->add_hp(-R);
            red_soldier->arrow_ptr->use_arrow();
            cout<<*game_timer<<' '<<*red_soldier<<" shot";
            if(city[city_id+1]->blue_soldier->get_hp()<=0){
                cout<<" and killed "<<*city[city_id+1]->blue_soldier;
            }
            cout<<endl;
            if(red_soldier->arrow_ptr->get_remain()<=0)
                red_soldier->lose_weapon(2);
        }
    }
    if(blue_soldier && blue_soldier->arrow_ptr && city_id != 1){
        if(city[city_id-1]->red_soldier){
            city[city_id-1]->red_soldier->add_hp(-R);
            blue_soldier->arrow_ptr->use_arrow();
            cout<<*game_timer<<' '<<*blue_soldier<<" shot";
            if(city[city_id-1]->red_soldier->get_hp()<=0){
                cout<<" and killed "<<*city[city_id-1]->red_soldier;
            }
            cout<<endl;
            if(blue_soldier->arrow_ptr->get_remain()<=0)
                blue_soldier->lose_weapon(2);
        }
    }
}
void City::do_clear_shot(){
    //清理35分钟 仅1人的死尸
    if(battle_stauts && (red_soldier->get_hp()>0 || blue_soldier->get_hp()>0)) return;
    if(red_soldier && red_soldier->get_hp()<=0){
        red_soldier->die();
    }
    if(blue_soldier && blue_soldier->get_hp()<=0){
        blue_soldier->die();
    }
}
void City::do_battle(){
    //第38分钟调用并判断炸弹 第40检测死亡
    if(!red_soldier || !blue_soldier || !battle_stauts) return;
    if(red_soldier->get_type()=="lion") ((lion*)red_soldier)->set_last_hp(red_soldier->hp>0?red_soldier->hp:0);
    if(blue_soldier->get_type()=="lion") ((lion*)blue_soldier)->set_last_hp(blue_soldier->hp>0?blue_soldier->hp:0);
    if(red_soldier->hp<=0 || blue_soldier->hp<=0) return;//被箭射死则没有战斗
    soldier*& first_s = (flag_type&1)?red_soldier:blue_soldier;
    soldier*& second_s = (flag_type&1)?blue_soldier:red_soldier;
    first_s->attack_other(second_s);
    //不可能同时死亡
    if(first_s->get_hp()>0 && second_s->get_hp()>0){
        return;
    }
    soldier*& winner = first_s->get_hp()>0 ? first_s :second_s;
    soldier*& loser = first_s->get_hp()>0 ? second_s :first_s;
    if(loser->bomb_ptr){
        //有炸弹
        cout << *game_timer << ' '<<loser->get_team_name()<<' '<<loser->get_type()<<' '<<loser->get_uid();
        cout << " used a bomb and killed "<<winner->get_team_name()<<' '<<winner->get_type()<<' '<<winner->get_uid()<<endl;
        winner->die();
        loser->die();
        battle_stauts = false;//自爆不视为战斗
        sst.str("");
        return;
    }
    game_timer->set_minite(40);
    sst<<*game_timer<<' '<<*loser<<" was killed in city "<<city_id<<endl;
    game_timer->set_minite(38);
    //死亡事件在第40分钟时结算
}
void City::do_balance_01(){
    //第40分钟结算内容 收割装备->死亡->奖励->收割生命元
    //第一次遍历：战斗、战死结算，欢呼

    if(!red_soldier || !blue_soldier || !battle_stauts){
        sst.str("");
        return;
    }
    //sst留着
    if(red_soldier->get_hp()>0 && blue_soldier->get_hp()>0){
        //双活
        if(red_soldier->get_type()=="dragon"){
            ((dragon*)red_soldier)->add_morale(-0.2);
        }
        if(blue_soldier->get_type()=="dragon"){
            ((dragon*)blue_soldier)->add_morale(-0.2);
        }
        if(red_soldier->get_type()=="lion"){
            ((lion*)red_soldier)->add_loyalty(-K);
        }
        if(blue_soldier->get_type()=="lion"){
            ((lion*)blue_soldier)->add_loyalty(-K);
        }
    }else{
        soldier*& winner = red_soldier->get_hp()>0 ? red_soldier :blue_soldier;
        soldier*& loser = red_soldier->get_hp()>0 ? blue_soldier :red_soldier;
        if(winner->get_type()=="wolf")loser->being_stolen_weapon(winner);
        if(winner->get_type()=="dragon")((dragon*)winner)->add_morale(0.2);
        if(loser->get_type()=="lion")winner->add_hp(((lion*)loser)->get_last_hp());
        //被杀死 或被箭射死
        loser->die();
    }
    //若被箭射死，则sst为空（35分钟已输出过）。否则有攻击信息与死亡信息

    if((flag_type&1) && red_soldier && red_soldier->get_type()=="dragon"){
        if(((dragon*)red_soldier)->get_morale()>0.8)
            sst<<*game_timer<<' '<< *red_soldier<<" yelled in city "<<city_id<<endl;
    }
    if(!(flag_type&1) && blue_soldier && blue_soldier->get_type()=="dragon"){
        if(((dragon*)blue_soldier)->get_morale()>0.8)
            sst<<*game_timer<<' '<<*blue_soldier<<" yelled in city "<<city_id<<endl;
    }
    //先假装输出获取生命元，然后再重新收割
}
void City::do_balance_02(bool red){
    //40分钟第二次遍历：发送生命元，无输出
    //红队逆向遍历 蓝队顺向遍历
    if(!battle_stauts) return;//无战斗不发
    if(red_soldier && blue_soldier) return;//双活不发
    if(!red_soldier && !blue_soldier) return;//仅单活发
    if(red){
        if(!red_soldier) return;
        if(red_team->get_hp_money()>=8){
            red_team->add_hp_money(-8);
            red_soldier->add_hp(8);
        }
    }else{
        if(!blue_soldier) return;
        if(blue_team->get_hp_money()>=8){
            blue_team->add_hp_money(-8);
            blue_soldier->add_hp(8);
        }
    }

}
void City::do_balance_03(){
    //40分钟第三次遍历：获取生命元、升旗、输出
    if(!battle_stauts) return;
    cout<<sst.str();
    sst.str("");
    battle_stauts = false; //复位
    if(red_soldier && blue_soldier){
        //双活
        last_winner = 0;//无上一次赢家
        return;
    }
    //理论上不存在双死的情形，为了安全
    if(!red_soldier && !blue_soldier) return;
    int current_winner = red_soldier? 3 :2;
    soldier*& winner = red_soldier?red_soldier:blue_soldier;
    cout<<*game_timer<<' '<<*winner<<" earned "<<element<<" elements for his headquarter"<<endl;
    if(red_soldier){
        red_team->add_hp_money(element);
    }else{
        blue_team->add_hp_money(element);
    }
    element = 0;
    //开始升旗
    if(current_winner == last_winner && flag_type !=current_winner){
        flag_type = current_winner;
        cout << *game_timer << ' '<<winner->get_team_name()<<" flag raised in city "<<city_id<<endl;
    }
    last_winner = current_winner;
}

void lion::check_escape(){
    //cout << "loyalty = "<<loyalty<<endl;
    if(loyalty > 0) return;
    cout << *game_timer <<' '<<get_team_name()<<" lion "<<get_uid()<<" ran away"<<endl;
    if(get_team_name() == "red"){
        red_team->delete_soldier(this);
        city[city_id]->red_soldier=NULL;
    }else{
        blue_team->delete_soldier(this);
        city[city_id]->blue_soldier=NULL;
    }
    delete this;
}
void soldier::move_next(){
    if(get_team_name()=="red"){
        if(city_id==N+1) return;
        city[city_id]->red_soldier=NULL;
        city[++city_id]->red_soldier=this;
        if(city_id==N+1) blue_team->add_enemy_num();
    }else{
        if(city_id==0) return;
        //cout<<city_id<<endl;
        city[city_id]->blue_soldier=NULL;
        city[--city_id]->blue_soldier=this;
        if(city_id==0) red_team->add_enemy_num();
    }
    if(get_type()=="iceman"){
        ((iceman*)this)->step_cont++;
        if(((iceman*)this)->step_cont%2==0){
            hp-=9;
            if(hp<1) hp=1;
            atk+=20;
        }
    }
}
void soldier::die(){
    //在调用die()前应先缴获武器
    //清除记录+清除士兵数据
    if(team_name=="red"){
        red_team->delete_soldier(this);
        city[city_id]->red_soldier = NULL;
    }else{
        blue_team->delete_soldier(this);
        city[city_id]->blue_soldier = NULL;
    }
    //↓史上我写过的最心跳的东西↓
    delete this;
}

void Game_Run(){
    //GameTimer& current_time = *game_timer;
    bool red_finished = false, blue_finished = false;
    while(game_timer->get_t_minute()<=T){
        // The main loop

        game_timer->set_minite(0);
        if(game_timer->get_t_minute()>T) break;
            red_team->create_soldier();
            blue_team->create_soldier();

        game_timer->set_minite(5);
        if(game_timer->get_t_minute()>T) break;
            for(int i=0;i<=N+1;i++){
                //cout<<"city[i]"<<i<<"\n";
                city[i]->do_escape();
            }

        game_timer->set_minite(10);
        if(game_timer->get_t_minute()>T) break;
            red_team->do_move();
            blue_team->do_move();
            if(city[0]->blue_soldier && !city[0]->blue_soldier->arrive_tag){
                city[0]->blue_soldier->arrive_tag = true;
                cout<<*game_timer<<" blue "<<city[0]->blue_soldier->get_type()<<' '<<city[0]->blue_soldier->get_uid()<<" reached red headquarter with ";
                cout<<city[0]->blue_soldier->get_hp()<< " elements and force "<<city[0]->blue_soldier->get_atk()<<endl;
                if(red_team->get_enemy_num() >= MAX_ENEMY_NUM){
                   blue_finished = true;
                   cout<<*game_timer<<" red headquarter was taken"<<endl;
                }
            }
            for(int i=1;i<=N;i++){
                if(city[i]->red_soldier){
                    cout<<*game_timer<<" red "<<city[i]->red_soldier->get_type()<<' '<<city[i]->red_soldier->get_uid()<<" marched to city ";
                    cout<<i<<" with "<<city[i]->red_soldier->get_hp()<<" elements and force "<<city[i]->red_soldier->get_atk()<<endl;
                }
                if(city[i]->blue_soldier){
                    cout<<*game_timer<<" blue "<<city[i]->blue_soldier->get_type()<<' '<<city[i]->blue_soldier->get_uid()<<" marched to city ";
                    cout<<i<<" with "<<city[i]->blue_soldier->get_hp()<<" elements and force "<<city[i]->blue_soldier->get_atk()<<endl;
                }
            }
            if(city[N+1]->red_soldier && !city[N+1]->red_soldier->arrive_tag){
                city[N+1]->red_soldier->arrive_tag = true;
                cout<<*game_timer<<" red "<<city[N+1]->red_soldier->get_type()<<' '<<city[N+1]->red_soldier->get_uid()<<" reached blue headquarter with ";
                cout<<city[N+1]->red_soldier->get_hp()<< " elements and force "<<city[N+1]->red_soldier->get_atk()<<endl;
                if(blue_team->get_enemy_num() >= MAX_ENEMY_NUM){
                    red_finished = true;
                    cout<<*game_timer<<" blue headquarter was taken"<<endl;
                }
            }
            if(red_finished || blue_finished) break;

        game_timer->set_minite(20);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++)
                city[i]->create_element();

        game_timer->set_minite(30);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++)
                city[i]->do_gain_element();

        game_timer->set_minite(35);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++)
                city[i]->do_shoot();
            for(int i=1;i<=N;i++)
                city[i]->do_clear_shot();

        game_timer->set_minite(38);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++)
                city[i]->do_battle();

        game_timer->set_minite(40);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++)
                city[i]->do_balance_01();
            for(int i=1;i<=N;i++)
                city[i]->do_balance_02(false);
            for(int i=N;i>=1;i--)
                city[i]->do_balance_02(true);
            for(int i=1;i<=N;i++)
                city[i]->do_balance_03();

        game_timer->set_minite(50);
        if(game_timer->get_t_minute()>T) break;
            red_team->report_elements();
            blue_team->report_elements();

        game_timer->set_minite(55);
        if(game_timer->get_t_minute()>T) break;
            for(int i=0;i<=N+1;i++)
                city[i]->do_report_weapon(true);
            for(int i=0;i<=N+1;i++)
                city[i]->do_report_weapon(false);

        game_timer->add_time(5);
    }
}

int main(){
    int TT;
    cin>>TT;
    for(int ii=1;ii<=TT;ii++){
        cin>>M>>N>>R>>K>>T;
        for(int i=0;i<MAX_TYPE;i++)
            cin>>init_hp[i];
        for(int i=0;i<MAX_TYPE;i++)
            cin>>init_atk[i];
        game_timer = new GameTimer;
        red_team = new RedTeam(M);
        blue_team = new BlueTeam(M);
        for(int i=0;i<=N+1;i++)
            city.push_back(new City(i));

        cout<<"Case "<<ii<<':'<<endl;
        Game_Run();

        delete red_team;
        delete blue_team;
        delete game_timer;
        for(int i=0;i<=N+1;i++)
            delete city[i];
        city.clear();
    }
    return 0;
}
