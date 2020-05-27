
#define SniperCommandrHealth 120
class SniperCommander:public Sniper
{
private:
    /* data */
public:
    SniperCommander(int player):Sniper{player,SniperCommandrHealth}{};;
    ~SniperCommander();
};
