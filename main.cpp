#include <fstream>
#include "Automaton.h"
using namespace std;
ifstream fin("automaton.in");
ofstream fout("automaton.out");

int main()
{
    Automaton AFN;
    fin>>AFN;
    AFN.ConvertNFAtoDFA();
    fout<<AFN;
    return 0;
}
