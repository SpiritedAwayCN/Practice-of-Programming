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
#define MAX_ENEMY_NUM 1
#define OUTPUT_HOUR_ONLY false

//#define cout ost
//#define cin ist

using namespace std;
//ifstream ist("input-3.txt");
//ofstream ost("my_output.txt");
int init_hp[MAX_TYPE];
int init_atk[MAX_TYPE];
int M,N,K,T;

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
    bomb(int natk = 4)
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
    , remain(2)
    {
    }
    string get_type_name() const {return "arrow";}
    int get_type_id() const {return 2;}
    int get_remain() const {return remain;}
    int use_arrow() {remain--;};
private:
    int remain;
};
struct prepare_comp{
    bool operator()(Weapon* wep1, Weapon* wep2){
        if(wep1->get_type_id() == wep2->get_type_id() && wep1->get_type_id() ==2){
            return ((arrow*)wep1)->get_remain() < ((arrow*)wep2)->get_remain();
        }
        return wep1->get_type_id() < wep2->get_type_id();
    }
};
struct stolen_comp{
    bool operator()(Weapon* wep1, Weapon* wep2){
        if(wep1->get_type_id() == wep2->get_type_id() && wep1->get_type_id() ==2){
            return ((arrow*)wep1)->get_remain() > ((arrow*)wep2)->get_remain();
        }
        return wep1->get_type_id() < wep2->get_type_id();
    }
};

class soldier{
public:
    void add_hp(int num){hp+=num;}
    void set_atk(int num){atk=num;}
    int get_uid() const{return uid;}
    int get_hp() const{return hp;}
    int get_atk() const{return atk;}
    string get_team_name() const {return team_name;}
    virtual string get_type() const = 0;
    void prepare_weapon(){
        if(equipped_weapon.empty()) return;
        equipped_weapon.sort(prepare_comp());
        use_iter=equipped_weapon.begin();
    }
    void lose_weapon(Weapon* wep){
        equipped_weapon.remove(wep);
        delete wep;
    }
    void die();
    Weapon* get_weapon(int index){
        if(index<0 || index >= equipped_weapon.size()) return NULL;
        int cont=0;
        for(list<Weapon*>::iterator iter=equipped_weapon.begin();iter!=equipped_weapon.end();iter++){
            if(cont==index) return *iter;
            cont++;
        }
        return NULL;
    }

    bool gain_weapon(int type_id){
        if(equipped_weapon.size()>=MAX_WEAPON) return false;
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
    bool gain_weapon(Weapon* Wep){
        if(equipped_weapon.size()>=MAX_WEAPON) return false;
        equipped_weapon.push_back(Wep);
        return true;
    }
    void move_next();
    void report_weapons(){
        cout << *game_timer<<' '<<get_team_name()<<' '<<get_type()<<' '<<get_uid()<<" has ";
        int cont[3]={0,0,0};
        for(list<Weapon*>::iterator iter = equipped_weapon.begin(); iter != equipped_weapon.end();++iter)
            cont[(*iter)->get_type_id()]++;
        cout<<cont[0]<<" sword "<<cont[1]<<" bomb "<<cont[2]<<" arrow and "<<hp<<" elements"<<endl;
    }
    void being_stolen_weapon(soldier* source, bool wolf = true){
        if(equipped_weapon.empty()) return;
        equipped_weapon.sort(stolen_comp());
        list<Weapon*>::iterator iter = equipped_weapon.begin();
        Weapon* st_id = *iter;
        int cont = 0;
        while(iter != equipped_weapon.end()){
            if(wolf && st_id->get_type_id() != (*iter)->get_type_id()) break;
            if(!source->gain_weapon(*iter)) break;
            cont++;
            equipped_weapon.erase(iter++);
        }
        if(wolf){
            cout<<*game_timer<<' '<<source->get_team_name()<<" wolf "<<source->get_uid()<<" took "<<cont;
            cout<<' '<<st_id->get_type_name()<<" from "<<get_team_name()<<' '<<get_type()<<' '<<get_uid();
            cout<<" in city "<<city_id<<endl;
        }
    }
    bool attack_other(soldier* target){
        if(equipped_weapon.empty()) return false;
        int real_atk = (*use_iter)->get_atk_rate() * atk / 10;
        list<Weapon*>::iterator iter = equipped_weapon.end();
        --iter;
        //都是sword 攻击相同
        if(real_atk == 0 && (*iter)->get_type_id()==0) return false;
        switch((*use_iter)->get_type_id()){
        case 0:
            //if(real_atk==0) return false;
            target->add_hp(-real_atk);
            use_iter++;
            break;
        case 1:
            target->add_hp(-real_atk);
            if(get_type()!="ninja") add_hp(-real_atk/2);
            equipped_weapon.erase(use_iter++);
            break;
        case 2:{
            arrow* ptr = (arrow*)(*use_iter);
            target->add_hp(-real_atk);
            ptr->use_arrow();
            if(!ptr->get_remain()){
                equipped_weapon.erase(use_iter++);
            }
            else
                use_iter++;
            break;
        }
        }
        if(use_iter==equipped_weapon.end() && !equipped_weapon.empty())
            use_iter = equipped_weapon.begin();
        return true;
    }
    virtual ~soldier(){
        for(list<Weapon*>::iterator iter = equipped_weapon.begin(); iter != equipped_weapon.end();++iter)
            delete *iter;
    }
protected:
    soldier(const string& team,int id,int nhp,int natk)
    : uid(id)
    , hp(nhp)
    , atk(natk)
    , team_name(team)
    {
        if(team == "red") city_id = 0;
        else city_id = N+1;
    }
    int city_id;
private:
    list<Weapon*> equipped_weapon;
    list<Weapon*>::iterator use_iter;

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
    {
        gain_weapon(get_uid()%3);
    }
    string get_type() const{return "iceman";}
};
class lion : public soldier{
public:
    lion(const string& team,int id,int hp_mon,int nhp = init_hp[3],int natk = init_atk[3])
    : soldier(team,id,nhp,natk)
    , loyalty(hp_mon - nhp)
    {
        gain_weapon(get_uid()%3);
    }
    string get_type() const{return "lion";}
    int get_loyalty() const{return loyalty;}
    void add_loyalty(int num) {loyalty+=num;}
    void check_escape();
private:
    int loyalty;
};
class wolf : public soldier{
public:
    wolf(const string& team,int id,int nhp = init_hp[4],int natk = init_atk[4])
    : soldier(team,id,nhp,natk)
    {
    }
    string get_type() const{return "wolf";}
};

class City{
public:
    City(int id)
    : city_id(id)
    , red_soldier(NULL)
    , blue_soldier(NULL)
    {
    }
    //soldiers will be destructed in ~command()
    soldier* red_soldier;
    soldier* blue_soldier;
    void do_escape(){
        if(red_soldier && red_soldier->get_type() == "lion")
            ((lion*)red_soldier)->check_escape();
        if(blue_soldier && blue_soldier->get_type() == "lion")
            ((lion*)blue_soldier)->check_escape();
    }
    void do_report_weapon(){
        if(red_soldier) red_soldier->report_weapons();
        if(blue_soldier) blue_soldier->report_weapons();
    }
    void do_stole_weapon(){
        if(!red_soldier || !blue_soldier) return;
        if(red_soldier->get_type() == "wolf" && blue_soldier->get_type() != "wolf"){
            blue_soldier->being_stolen_weapon(red_soldier,true);
        }else if(blue_soldier->get_type() == "wolf" && red_soldier->get_type() != "wolf"){
            red_soldier->being_stolen_weapon(blue_soldier,true);
        }
    }
    void do_battle(){
        if(!red_soldier || !blue_soldier) return;
        soldier*& first_s = (city_id&1)?red_soldier:blue_soldier;
        soldier*& second_s = (city_id&1)?blue_soldier:red_soldier;
        first_s->prepare_weapon();
        second_s->prepare_weapon();
        //system("pause");
        bool red_atk = true, blue_atk = true;
        while(first_s->get_hp()>0 && second_s->get_hp()>0){
            if(red_atk) red_atk=first_s->attack_other(second_s);
            if(first_s->get_hp()<=0 || second_s->get_hp()<=0) break;
            if(blue_atk) blue_atk=second_s->attack_other(first_s);
            if(red_atk == false && blue_atk == false) break;
        }
        cout << *game_timer << ' ';
        if(first_s->get_hp()>0 && second_s->get_hp()>0){
            cout << "both red "<<red_soldier->get_type()<<' '<<red_soldier->get_uid();
            cout << " and blue "<<blue_soldier->get_type()<<' '<<blue_soldier->get_uid();
            cout << " were alive in city "<<city_id<<endl;
            if(red_soldier->get_type()=="dragon")
                cout<<*game_timer<<' '<<red_soldier->get_team_name()<<" dragon "<<red_soldier->get_uid()<<" yelled in city "<<city_id<<endl;
            if(blue_soldier->get_type()=="dragon")
                cout<<*game_timer<<' '<<blue_soldier->get_team_name()<<" dragon "<<blue_soldier->get_uid()<<" yelled in city "<<city_id<<endl;
        }else if(first_s->get_hp()<=0 && second_s->get_hp()<=0){
            cout << "both red "<<red_soldier->get_type()<<' '<<red_soldier->get_uid();
            cout << " and blue "<<blue_soldier->get_type()<<' '<<blue_soldier->get_uid();
            cout << " died in city "<<city_id<<endl;
            first_s->die();
            second_s->die();
        }else{
            soldier*& winner = first_s->get_hp()>0 ? first_s :second_s;
            soldier*& loser = first_s->get_hp()>0 ? second_s :first_s;
            cout<<winner->get_team_name()<<' '<<winner->get_type()<<' '<<winner->get_uid()<<" killed ";
            cout<<loser->get_team_name()<<' '<<loser->get_type()<<' '<<loser->get_uid()<<" in city ";
            cout<<city_id<<" remaining "<<winner->get_hp()<<" elements"<<endl;
            if(winner->get_type()=="dragon"){
                cout<<*game_timer<<' '<<winner->get_team_name()<<" dragon "<<winner->get_uid()<<" yelled in city "<<city_id<<endl;
            }
            loser->being_stolen_weapon(winner , false);
            loser->die();
        }
    }
private:
    int city_id;
};
vector<City*> city;


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
            //sst << "It has a "<<new_soldier->get_weapon(0)->get_type_name();
            //sst.setf(ios::fixed);
            //sst << ",and it's morale is " << setprecision(2) << ((dragon*)new_soldier)->get_morale()<<'\n';
            break;
        case 1:
            new_soldier = new ninja(get_team_color(),get_total_soldier(),get_hp_money());
            //sst << "It has a "<<new_soldier->get_weapon(0)->get_type_name();
            //sst << " and a " <<new_soldier->get_weapon(1)->get_type_name()<<'\n';
            break;
        case 2:
            new_soldier = new iceman(get_team_color(),get_total_soldier(),get_hp_money());
            //sst << "It has a "<<new_soldier->get_weapon(0)->get_type_name()<<'\n';
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
        //cout<< " in " << get_team_color() << " headquarter"<<endl;
        cout<< sst.str();
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
    if(get_type()=="iceman")
        hp-=hp/10; //won't die
    else if(get_type()=="lion")
        ((lion*)this)->add_loyalty(-K);
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
            if(city[0]->blue_soldier){
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
            if(city[N+1]->red_soldier){
                cout<<*game_timer<<" red "<<city[N+1]->red_soldier->get_type()<<' '<<city[N+1]->red_soldier->get_uid()<<" reached blue headquarter with ";
                cout<<city[N+1]->red_soldier->get_hp()<< " elements and force "<<city[N+1]->red_soldier->get_atk()<<endl;
                if(blue_team->get_enemy_num() >= MAX_ENEMY_NUM){
                    red_finished = true;
                    cout<<*game_timer<<" blue headquarter was taken"<<endl;
                }
            }
            if(red_finished || blue_finished) break;

        game_timer->set_minite(35);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++){
                city[i]->do_stole_weapon();
            }

        game_timer->set_minite(40);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++){
                city[i]->do_battle();
            }

        game_timer->set_minite(50);
        if(game_timer->get_t_minute()>T) break;
            red_team->report_elements();
            blue_team->report_elements();

        game_timer->set_minite(55);
        if(game_timer->get_t_minute()>T) break;
            for(int i=1;i<=N;i++)
                city[i]->do_report_weapon();

        game_timer->add_time(5);
    }
}

int main(){
    int TT;
    cin>>TT;
    for(int ii=1;ii<=TT;ii++){
        cin>>M>>N>>K>>T;
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
