#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <fstream>
#include <vector>
using namespace std;

struct transition
{
    int state1, state2;
    char character;
};

class Automaton
{
    int numberStates;
    int *States;
    int numberCharacters;
    char *Alphabet;
    int numberFinalStates;
    int *FinalStates;
    int numberTransitions;
    transition *Transitions;
    int InitialState;
    int accepted; //0 pt nu, 1 pt da

    int numberStatesDFA,numberTransitionsDFA;
    vector< vector<int> > StatesDFA;
    transition *TransitionsDFA;

public:
    Automaton();
    Automaton(int, int, int, int);
    ~Automaton();
    void ConvertNFAtoDFA();
    bool VerificationWord (char *, int, int);
    void Reset() {accepted=0;};
    int GetInitalState() const {return InitialState;};

    friend ifstream & operator >> (ifstream &, Automaton &);
    friend ofstream & operator << (ofstream &, Automaton &);


};

#endif // AUTOMATON_H
