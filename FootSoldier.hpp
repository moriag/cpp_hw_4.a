
#define FootSoldierHealth 100
class FootSoldier:public Soldier
{
private:
protected:
    FootSoldier(int player,int health):Soldier{player,health}{}
public:
    FootSoldier(int player):Soldier{player,FootSoldierHealth}{}
    ~FootSoldier();
};

FootSoldier::~FootSoldier()
{
}
