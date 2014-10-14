/*
    Authors:
        Jake Osselaer & Quincy Schurr
 */


#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

class SortingCompetition
{
private:

    vector <char*> wordsVector;
    char ** words;
    char** wordsCopy;
    char** wordsLength;
    string input;
    int counter;

    void quickSortTest(char**&, int, int);
    int ThreePivotLength(char**&, int, int);

    int medianof5(char**, int, int);
    char medianof5alpha(char**, int, int);

    int findMedianLength(char**, int, int);
    char findMedianAlpha(char**, int, int);

    void quickSortLength(char**&, int, int);
    void quickSortAlpha(char**&, int, int);
    int partitionAlpha(char**&, int, int);
    int partitionLength(char**&, int, int);
    string getFileName();
    void lengthAlpha2(char**&);


public:

    void outputData(const string& outputFileName);
    bool prepareData();
    bool readData();
    void setFileName(const string& inputFileName);
    void sortData();


    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
