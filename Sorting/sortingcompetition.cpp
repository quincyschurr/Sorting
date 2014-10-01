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

    ifstream fin(this->input.c_str());//add a file to read in
    string parse;

    if(!fin)
    {
        cerr << "This file could not be opened" << endl;
        exit(1);
    }

    while(!fin.eof())
    {
        fin >> parse;
        words.push_back(parse);
    }


    //fin.getline(buffer, 81);

            /*while (1)
            {
                if(*buffer == startPage)
                {

                    memset(buffer, 0, 81 * sizeof(char));
                    fin.getline(buffer,81);

                    temp = splitWords(buffer, wordSize, amntOfWords, wordActual);
                    }
                   }*/

   /* char** splitWords(char* buffer, int size, int& amntOfWords, int& wordActual)
    {
        char** builder = new char*[size];
        int index = 0;

        // Pointer to the last word
        char* bufferPt = buffer;

        do
        {

            if(*buffer == '[')
            {

                buffer++;
                bufferPt = buffer;

                while(*buffer != ']')
                {
                    ++buffer;
                }

                *(buffer++) = '\0';
                builder[index] = new char[strlen(bufferPt) + 1];
                strcpy(builder[index++], bufferPt);

                buffer++; //ignores the space

                bufferPt = buffer;
            }

            else if(*buffer == ' ')
            {

                *(buffer++) = '\0';

                builder[index] = new char[strlen(bufferPt) + 1];
                strcpy(builder[index++], bufferPt);

                bufferPt = buffer;

            }

            else if (*(buffer + 1) == '\0')
            {
                ++buffer;

                builder[index] = new char[strlen(bufferPt) + 1];
                strcpy(builder[index++], bufferPt);

                bufferPt = buffer;
            }

            else
            {
                ++buffer;
            }

        } while (*buffer != '\0');

        wordActual += index;
        amntOfWords = index;
        return builder;
    }*/





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

SortingCompetition::~SortingCompetition()
{

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
