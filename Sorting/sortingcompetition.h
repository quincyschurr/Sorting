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
    string inputFileName;

public:

    void outputData(const string& outputFileName);
    bool prepareData();
    bool readData();
    void setFileName(const string& inputFileName);
    void sortData();
    void quickSort(int*&, int, int);
    int partition(int*&, int, int);

    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
