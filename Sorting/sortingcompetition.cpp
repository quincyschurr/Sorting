/*
    Authors:
        Jake Osselaer & Quincy Schurr
 */



#include "sortingcompetition.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>

using namespace std;

SortingCompetition::SortingCompetition()
{


}

SortingCompetition::SortingCompetition(const string &inputFileName)
{
    this->input = string(inputFileName);
    counter = 0;
}

string SortingCompetition::getFileName()
{
    return this->input;
}

void SortingCompetition::outputData(const string& outputFileName)
{
    fstream out(outputFileName.c_str());
    out << "WE ARE GETTING TO THE OUTPUT METHOD" << endl;

    out << "Prints sorted by length" << endl;
    for(int i = 0; i < counter; i++) {
        out << wordsLength[i] << " ";
    }
    out << endl << endl;

    out << "Prints sorted by ASCII" << endl;
    for(int i = 0; i < counter; i++) {
        out << wordsAlpha[i] << " ";
    }

    delete words;
    delete wordsAlpha;
    delete wordsLength;
    delete wordsCopy;
    //delete wordsVector;
}

bool SortingCompetition::prepareData()
{
    wordsCopy = new char*[counter];
    wordsAlpha = new char*[counter];
    wordsLength = new char*[counter];

    cout << "This is executing in prepareData " << endl;

    for(int j = 0; j < counter; j++)
    {
        wordsCopy[j] = words[j];
        wordsAlpha[j] = words[j];
        wordsLength[j] = words[j];
    }

}

bool SortingCompetition::readData()
{
    cout << "This is the beginning of readData" << endl;

    char* temporary;
    //char* buffer;

   // wordsVector = new vector<char*>(100);

    ifstream fin(this->input.c_str());//add a file to read in

    if(!fin)
    {
        cerr << "This file could not be opened" << endl;
        exit(1);
    }



    /*while(!fin.eof())
    {
        fin >> temporary;
        buffer = new char[temporary.length()];
        memset(buffer, 0, (temporary.length()) * sizeof(char));

        int temporarySize = temporary.length();

        for(int k = 0; k < temporarySize; k++)
        {
            buffer[k] = temporary[k];
        }

        wordsVector.push_back(buffer);
        counter++;
    }*/
    counter = 0;
    while(!fin.eof()) {
        temporary = new char[100];
        fin >> temporary;

        wordsVector.push_back(temporary);
        counter++;
    }

    words = new char*[counter];

    for(int i = 0; i < counter; i++)
    {
        words[i] = wordsVector[i];
        cout << "WORDS " << words[i] << endl;
    }

    cout << "This is the end of readData" <<endl;
}

void SortingCompetition::setFileName(const string& inputFileName)
{
    input = inputFileName.c_str();
    cout << "This is executing in setFileName" << endl;

}

void SortingCompetition::sortData()
{
    cout << "This is executing in sortData" << endl;

    //Just call in order of what we need sorted

    int left = 0;
    int right = counter - 1;

    quickSortLength(wordsLength, left, right);
    quickSortAlpha(wordsAlpha, left, right);

}

//maybe use char* with prefix
//quick sort with integers
void SortingCompetition::quickSortLength(char**& wordsLength, int left, int right)
{
    if ( left < right )
    {
        int mid = 0;
        mid = partitionLength(wordsLength, left, right);
        quickSortLength(wordsLength, left, mid-1);
        quickSortLength(wordsLength, mid+1, right);
    }
}
//partition for interger quickSort
int SortingCompetition::partitionLength(char**& wordsLength, int left, int right)
{
    //DEBUGGER IS STOPPING HERE!
    int pivot = strlen(wordsLength[left]);

    while ( left < right )
    {
        while ( strlen(wordsLength[left]) < pivot )
            left++;

        while ( strlen(wordsLength[right]) > pivot )
            right--;

        if ( strlen(wordsLength[left]) == strlen(words[right]) )
            left++;
        else if ( left < right )
        {
            char* temp = wordsLength[left];
            wordsLength[left] = wordsLength[right];
            wordsLength[right] = temp;
        }
    }

    return right;
}

//alphabetical quicksort
void SortingCompetition::quickSortAlpha(char**& wordsAlpha, int left, int right)
{
    if ( left < right )
    {
        int mid = partitionAlpha(wordsAlpha, left, right);
        quickSortAlpha(wordsAlpha, left, mid-1);
        quickSortAlpha(wordsAlpha, mid+1, right);
    }
}
//partition for alphabetical quickSort
int SortingCompetition::partitionAlpha(char**& wordsAlpha, int left, int right)
{
    char* pivot = wordsAlpha[right];

    while ( left < right )
    {
        //while ( wordsAlpha[left] < pivot )
        while(strcmp(wordsAlpha[left], pivot) <= -1)
            left++;

        //while ( wordsAlpha[right] > pivot )
        while(strcmp(wordsAlpha[right], pivot) >= 1)
            right--;

        //if ( strlen(wordsAlpha[left] == strlen(wordsAlpha[right]) )
        if(strcmp(wordsAlpha[left], wordsAlpha[right]) == 0)
            left++;
        else if ( left < right )
        {
            char* temp = wordsAlpha[left];
            wordsAlpha[left] = wordsAlpha[right];
            wordsAlpha[right] = temp;
        }
    }

    return right;

}

SortingCompetition::~SortingCompetition()
{

}
