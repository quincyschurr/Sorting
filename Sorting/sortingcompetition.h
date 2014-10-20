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
#include <thread>

using namespace std;

class SortingCompetition
{
private:

    vector <char*> wordsVector; //to store words as we read them in
    char ** words; //translate vector into char**
    char** wordsLength; //copy of words to use for sort
    char** temp;
    int * tempL; //temp lengths
    int * lengths;
    string input;//text file argument
    int counter;//for number of words

    int medianof5(int*, int, int);
    char* medianof5alpha(char**, int, int);

    int findMedianLength(char**, int, int);
    char* findMedianAlpha(char**, int, int);

    void merge(char**&, int, int, int); //maybe pass by reference
    void mergesort(char**&, int, int); //maybe pass by reference
    void mergeAlpha(char**&, int, int, int); //maybe pass by reference
    void mergesortAlpha(char**&, int, int); //maybe pass by reference

    void merge(char**&, int*&, int, int, int); //maybe pass by reference
    void mergesort(char**&, int*&, int, int); //maybe pass by reference

    //these functions all work with first element pivot
    string getFileName();
    void lengthAlpha2(char**&);
    void quickSortLength(char**&, int, int);
    void quickSortAlpha(char**&, int, int);
    int partitionAlpha(char**&, int, int);
    int partitionLength(char**&, int, int);

    void quickSortLength(char**&, int*&, int, int);
    int partitionLength(char**&, int*&, int, int);


public:

    void outputData(const string& outputFileName);
    bool prepareData();
    bool readData();
    void setFileName(const string& inputFileName);
    void sortData();

    //constructors and destructors
    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
