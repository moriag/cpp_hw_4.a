
#define ParamedicHealth 100
class Paramedic:public Soldier
{
private:
    /* data */
protected:
    Paramedic(int player,int health):Soldier{player,health}{}    
public:
    Paramedic(int player):Soldier{player,ParamedicHealth}{}
    ~Paramedic();
};


Paramedic::~Paramedic()
{
}
