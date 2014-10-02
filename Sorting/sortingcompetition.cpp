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
}

string SortingCompetition::getFileName()
{
    return this->input;
}

void SortingCompetition::outputData(const string& outputFileName)
{
    fstream out(outputFileName.c_str());
    out << "WE ARE GETTING TO THIS METHOD" << endl;
}

bool SortingCompetition::prepareData()
{

}

bool SortingCompetition::readData()
{

    string temporary;
    char* buffer;


    ifstream fin(this->input.c_str());//add a file to read in

    if(!fin)
    {
        cerr << "This file could not be opened" << endl;
        exit(1);
    }

    while(!fin.eof())
    {
        fin >> temporary;
        buffer = new char[temporary.length()];
        memset(buffer, 0, (temporary.length()) * sizeof(char));

        for(int i = 0; i < temporary.length(); i++)
        {
            buffer[i] = temporary[i];
        }

        words.push_back(buffer);
    }

}

void SortingCompetition::setFileName(const string& inputFileName)
{
    input = inputFileName.c_str();

}

void SortingCompetition::sortData()
{
    //I think we should use a median as a pivot
    //so we can just a common word with a letter that starts
    //in the middle of the alphabet like L or M
    //so a word like "land" "last" "love" "made" or "man"
    //and average word length is 5

}


//quick sort with integers
void SortingCompetition::quickSortLength(char **& words, int left, int right)
{
    if ( left < right )
    {
        int mid = SortingCompetition::partitionLength(words, left, right);
        quickSortLength(words, left, mid-1);
        quickSortLength(words, mid+1, right);
    }
}
//partition for interger quickSort
int SortingCompetition::partitionLength(char ** &words, int left, int right)
{
    int pivot = strlen(words[right]);

    while ( left < right )
    {
        while ( strlen(words[left]) < pivot )
            left++;

        while ( strlen(words[right]) > pivot )
            right--;

        if ( strlen(words[left]) == strlen(words[right]) )
            left++;
        else if ( left < right )
        {
            char* temp = words[left];
            words[left] = words[right];
            words[right] = temp;
        }
    }

    return right;
}

//alphabetical quicksort
void SortingCompetition::quickSortAlpha(char **& words, int left, int right)
{
    if ( left < right )
    {
        int mid = partitionAlpha(words, left, right);
        quickSortAlpha(words, left, mid-1);
        quickSortAlpha(words, mid+1, right);
    }
}
//partition for alphabetical quickSort
int SortingCompetition::partitionAlpha(char**& words, int left, int right)
{
    char* pivot = words[right];

    while ( left < right )
    {
        //while ( words[left] < pivot )
        while(strcmp(words[left], pivot) <= -1)
            left++;

        //while ( words[right] > pivot )
        while(strcmp(words[right], pivot) >= 1)
            right--;

        //if ( strlen(words[left] == strlen(words[right]) )
        if(strcmp(words[left], words[right]) == 0)
            left++;
        else if ( left < right )
        {
            char* temp = words[left];
            words[left] = words[right];
            words[right] = temp;
        }
    }

    return right;

}

SortingCompetition::~SortingCompetition()
{

}
