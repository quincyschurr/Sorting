#include "sortingcompetition.h"
#include <iomanip>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        cerr << "There are not enough files to run this program" << endl;
        cerr << "Expected arguments are ./a.out <input file> <output file>" << endl;
        return 1;
    }
    return 0;

    //create a SortingCompetition object
    SortingCompetition sc1(argv[1]);
    sc1.setFileName(argv[1]);

    sc1.outputData(argv[2]);

}
