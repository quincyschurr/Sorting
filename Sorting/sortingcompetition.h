#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class SortingCompetition
{
private:
    vector <string> words;
    string input;

    void quickSortLength(char**&, int, int);
    int partitionLength(char**&, int, int);
    string getFileName();

public:

    void outputData(const string& outputFileName);
    bool prepareData();
    bool readData();
    void setFileName(const string& inputFileName);
    void sortData();
/*<<<<<<< HEAD
    void quickSortLength(int*&, int, int);
    int partition(int*&, int, int);
=======
>>>>>>> 8f249ee491f78d1810ffa4966a7c67d1a5a2d471*/

    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
