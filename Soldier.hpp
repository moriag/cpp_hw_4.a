class Soldier
{
private:
    int player;
    int health;
public:
     Soldier(int player,int health):player(player),health(health){}
    ~Soldier(){}
    int get_player(){
        return player;
    }
};

