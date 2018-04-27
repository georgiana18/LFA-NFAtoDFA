#include <fstream>
#include "include/Automaton.h"
#include <iostream>
using namespace std;
ifstream fin("automaton.in");
ofstream fout("automaton.out");

int main()
{
    int option;
    cout<<"Optiuni:\n";
    cout<<"1.Verifica daca un cuvant nevid este acceptat de AFN-ul din fisierul de intrare.\n";
    cout<<"2.Afiseaza in fisierul de iesire AFD-ul corespunzator AFN-ului citit.\n";
    cout<<"Alege optiunea: ";
    cin>>option;
    Automaton AFN;
    fin>>AFN;
    if(option==1)
    {
        char word[50];
        cout<<"\nDati cuvantul: ";
        cin>>word;
        AFN.Reset();
        if(AFN.VerificationWord(word, AFN.GetInitalState(), 0)==true)
            cout<<"Cuvantul este acceptat\n";
        else cout<<"Cuvantul este neacceptat\n";
    }
    else if(option==2)
    {
        AFN.ConvertNFAtoDFA();
        fout<<AFN;
    }
    return 0;
}
