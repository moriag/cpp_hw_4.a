
#define FootCommandrHealth 150
class FootCommander:public FootSoldier
{
private:
    /* data */
public:
    FootCommander(int player):FootSoldier{player,FootCommandrHealth}{};
    ~FootCommander();
};

