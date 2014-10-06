/*
    Authors:
        Jake Osselaer & Quincy Schurr
 */

#include "sortingcompetition.h"
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{

    if(argc != 3)
    {
        cerr << "There are not enough files to run this program" << endl;
        cerr << "Expected arguments are ./a.out <input file> <output file>" << endl;
        return 1;
    }

    chrono::time_point<chrono::system_clock> start, end;


    //create a SortingCompetition object
    SortingCompetition sc1(argv[1]);
    sc1.setFileName(argv[1]);

    sc1.readData();
    sc1.prepareData();

    start = chrono::system_clock::now();
    sc1.sortData();
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "Finished computation at " << ctime(&end_time) << endl;
    cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    sc1.outputData(argv[2]);


    return 0;

}
