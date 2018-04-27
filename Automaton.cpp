#include "Automaton.h"
#include <vector>
#include <algorithm>
Automaton::Automaton()
{
    numberStates=0;
    numberCharacters=0;
    numberFinalStates=0;
    numberTransitions=0;
    InitialState=0;
}

/**
*
* @param numberStates represent an integer, the number of AFN states
* @param numberCharacters represent an integer, the number of alphabet characters of AFN
* @param numberFinalStates represent an integer, the number of final AFN states
* @param numberTransitions represent an integer, the number of AFN transitions
* @return an automaton, method represent parameterized constructor of class
*/
Automaton::Automaton(int numberStates, int numberCharacters, int numberFinalStates, int numeberTransitions)
{
    States=new int[numberStates];
    Alphabet=new char[numberCharacters];
    FinalStates=new int[numberFinalStates];
    Transitions=new transition[numberTransitions];
}

Automaton::~Automaton()
{
    delete []States;
    delete []Alphabet;
    delete []FinalStates;
    delete []Transitions;
    delete []TransitionsDFA;
    StatesDFA.clear();
}

/**
*
* @param file represent a file with data
* @param NFA represent an object of the type Automaton
* @return a file, from which is read the automaton
*/

ifstream & operator >> (ifstream & file, Automaton & NFA)
{
    file>>NFA.numberStates;

    NFA.States=new int[NFA.numberStates+1];
    for(int i=1; i<=NFA.numberStates; i++)
    {
        file>>NFA.States[i];
    }
    file>>NFA.numberCharacters;
    NFA.Alphabet=new char[NFA.numberCharacters+1];
    for(int i=1; i<=NFA.numberCharacters; i++)
    {
        file>>NFA.Alphabet[i];
    }
    file>>NFA.InitialState;
    file>>NFA.numberFinalStates;
    NFA.FinalStates=new int[NFA.numberFinalStates+1];
    for(int i=1; i<=NFA.numberFinalStates; i++)
    {
        file>>NFA.FinalStates[i];
    }
    file>>NFA.numberTransitions;
    NFA.Transitions=new transition[NFA.numberTransitions+1];
    for(int i=1; i<=NFA.numberTransitions; i++)
    {
        file>>NFA.Transitions[i].state1;
        file>>NFA.Transitions[i].character;
        file>>NFA.Transitions[i].state2;
    }
    return file;
}

/**
*
* @param file represent a file
* @param DFA represent an object of the type Automaton
* @return a file, where is write the automaton details
*/

ofstream & operator << (ofstream & file, Automaton & DFA)
{
    file<<"Nr Stari: "<<DFA.numberStatesDFA<<"\n";
    for(int i=1; i<=DFA.numberStatesDFA; i++)
    {
        file<<i<<" : { ";
        for(vector<int>::iterator it=DFA.StatesDFA[i-1].begin(); it!=DFA.StatesDFA[i-1].end(); it++)
        {
            file<<*it<<" ";
        }
        file<<"}\n";
    }
    file<<"\n";
    file<<"Number of Transitions: "<<DFA.numberTransitionsDFA<<"\n";
    for(int i=0; i<DFA.numberTransitionsDFA; i++)
    {
        file<<DFA.TransitionsDFA[i].state1<<" "<<DFA.TransitionsDFA[i].character<<" "<<DFA.TransitionsDFA[i].state2<<"\n";
    }
    return file;
}


void Automaton::ConvertNFAtoDFA()
{
    ///redefinim noi stari pentru automatul DFA corespunzator automatului NFA citit
    vector<int> step;
    ///vectorul step este initializat cu 0 elemente automat
    /// vect step, tine setul de stari din AFN care se transforma intr-o stare AFD
    StatesDFA.push_back(step);

    numberStatesDFA=1;
    StatesDFA[0].push_back(InitialState);        ///prima data punem starea initiala

    int last=0;
    numberTransitionsDFA=0;
    bool newState;
    TransitionsDFA=new transition[numberTransitions*1000];

    while(last<numberStatesDFA)                 ///last=ultima stare pe care am pus-o in tabel
    {
        for(int j=1; j<=numberCharacters; j++) ///pt fiecare litera din alfabet
        {
            step.clear();
            newState=1;                 ///newState=1-> avem o stare noua, altfel am mai gasit-o in pasii anteriori
            for(vector<int>::iterator it=StatesDFA[last].begin(); it!=StatesDFA[last].end(); it++)
                ///ultima stare adaugata in DFA , vedem daca duce la seturi noi de stari in NFA, adica stare noua in DFA
            {
                for(int i=1; i<=numberTransitions; i++)     ///pt toate tranzitiile din AFN
                {
                    ///daca tranzitia curenta pleaca din starea din setul curent de stari si are litera la care suntem
                    if(Transitions[i].state1== *it && Transitions[i].character==Alphabet[j])
                    {
                        bool found=0;
                        for(vector<int>::iterator st=step.begin(); st!=step.end(); st++)
                        {
                            ///verificam sa nu apara de 2 ori aceeasi stare in noul set de stari
                            if(*st==Transitions[i].state2)
                            {
                                found=1;
                                break;
                            }
                        }
                        if(found==0) step.push_back(Transitions[i].state2);
                    }
                }
            }
            if(step.size()==0) continue;    ///daca setul este vid, trecem mai departe
            sort(step.begin(),step.end());    ///sortam vectorul ca sa ne ajute la comparatii
            for(int i=0; i<numberStatesDFA; i++)
            {
                if(step==StatesDFA[i])
                    ///daca deja exista setul de stari nu-l mai adaugam ca stare in DFA
                {
                    TransitionsDFA[numberTransitionsDFA].state1=last+1;
                    TransitionsDFA[numberTransitionsDFA].state2=i+1;
                    TransitionsDFA[numberTransitionsDFA].character=Alphabet[j];
                    numberTransitionsDFA++;
                    ///insa daca deja exista inseamna ca avem tranzitie de la starea curenta la starea
                    ///care corespunde deja acestui set si adaugam tranzitia
                    newState=0;
                }
            }
            if(newState==1)
                ///daca nu exista setul,il adaugam ca stare in DFA si totodata si tranzitia
            {
                TransitionsDFA[numberTransitionsDFA].state1=last+1;
                TransitionsDFA[numberTransitionsDFA].state2=numberStatesDFA+1;
                TransitionsDFA[numberTransitionsDFA].character=Alphabet[j];
                numberTransitionsDFA++;
                StatesDFA.push_back(step);
                numberStatesDFA++;
                //Nr de stari creste
            }
        }
        last++;
        ///ultima stare de la care am creeat noi seturi de stari, nu e aceeasi cu numberStatesDFA
        ///deoarece o stare in DFA avand subset poate adauga mai multe stari cu diferite litere
    }
}
