
#define SniperHealth 100
class Sniper: public Soldier{
private:
    /* data */
protected:
    Sniper(int player,int health):Soldier{player,health}{}
public:
    Sniper(int player):Soldier(player,SniperHealth){}
    ~Sniper();
};

Sniper::~Sniper()
{
}
