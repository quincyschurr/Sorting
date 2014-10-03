/*
    Authors:
        Jake Osselaer & Quincy Schurr
 */


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

    vector <char*> wordsVector;
    char ** words;
    char** wordsAlpha;
    char** wordsLength;
    char** wordsCopy;
    string input;
    int counter;


    void quickSortLength(char**&, int, int);
    void quickSortAlpha(char**&, int, int);
    int partitionAlpha(char**&, int, int);
    int partitionLength(char**&, int, int);
    string getFileName();

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
