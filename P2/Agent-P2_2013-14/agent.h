#ifndef AGENT__
#define AGENT__

#include <string>
#include <vector>
using namespace std;

// -----------------------------------------------------------
//                              class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
    public:
        Agent():bump_(false), dirty_(false),last_turn_(0){
            vector<int> aux(20,0);
            vector<vector<int> > m(20,aux);
            M_ = m;
            x_=9;
            y_=9;
            orientacion_=0;
        }

        enum ActionType
        {
            actFORWARD,
            actTURN_L,
            actTURN_R,
            actSUCK,
            actIDLE
        };

        void Perceive(const Environment &env);
        ActionType Think();
    private:
        bool bump_, dirty_;
        int last_turn_, orientacion_, x_, y_;
        vector<vector<int> > M_;
    /************************************
        MAPA:
        pared=-1

        ORIENTACIÓN:
        norte=0
        este=1
        sur=2
        oeste=3

        GIRO:
        no_giro=0
        izq=1
        der=2
    ************************************/

};

string ActionStr(Agent::ActionType);

#endif
