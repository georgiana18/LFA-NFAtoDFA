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

    int numberStatesDFA,numberTransitionsDFA;
    vector< vector<int> > StatesDFA;
    transition *TransitionsDFA;

public:
    Automaton();
    Automaton(int, int, int, int);
    ~Automaton();
    void ConvertNFAtoDFA();

    friend ifstream & operator >> (ifstream &, Automaton &);
    friend ofstream & operator << (ofstream &, Automaton &);


};

#endif // AUTOMATON_H
