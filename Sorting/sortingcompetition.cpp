/*
    Authors:
        Jake Osselaer & Quincy Schurr
 */



#include "sortingcompetition.h"

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
    //fstream out(outputFileName.c_str(), ios::out);
    ofstream fout("output.txt", ios::out);

    cout << "WE ARE GETTING TO THE OUTPUT METHOD" << endl;

    fout << "Prints sorted by length" << endl;
    for(int i = 0; i < counter; i++)
    {
        fout << wordsLength[i] << endl;
    }
    fout << endl << endl;

    fout << "Prints sorted by ASCII" << endl;
    for(int i = 0; i < counter; i++)
    {
        fout << wordsAlpha[i] << endl;
    }

    //we have to go through and do a deep delete as well.
    //with a for loop

    delete[] words;
    delete[] wordsAlpha;
    delete[] wordsLength;
    delete[] wordsCopy;

    fout.close();
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
        buffer = new char[temporary.length() + 1];
        memset(buffer, 0, (temporary.length() + 1) * sizeof(char));

        for(int k = 0; k < temporary.length(); k++)
        {
            buffer[k] = temporary[k];
        }

        wordsVector.push_back(buffer);
        counter++;
    }

    words = new char*[counter];

    for(int i = 0; i < counter; i++)
    {
        words[i] = wordsVector[i];
    }

    cout << "This is the end of readData" <<endl;
    fin.close();
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
//quick sort with integers
void SortingCompetition::quickSortLength(char**& wordsLength, int left, int right)
{
    int size = right;
    if ( left < right )
    {
        int mid = 0;
        mid = partitionLength(wordsLength, left, right);
        quickSortLength(wordsLength, left, mid-1);
        quickSortLength(wordsLength, mid+1, right);
    }

    //sorts each length alphabetically
    int max = strlen(wordsLength[size]);
    int lengthCount = 0;
    int startIndex = 0;
    int endIndex = 0;

    for(int r = 0; r < max; r++)
    {
        while(wordsLength[lengthCount][0] == r)
        {
            lengthCount++;
            endIndex++;
        }

        lengthCount = 0;
        char** temp = new char*[endIndex+1];
        for(int j = startIndex; j <= endIndex; j++)
        {
            temp[lengthCount] = wordsLength[j];
            lengthCount++;
        }

        quickSortAlpha(temp, 0, lengthCount - 1);
        lengthCount = 0;
        for(int k = startIndex; k <= endIndex; k++)
        {
            wordsLength[k] = temp[lengthCount];
            lengthCount++;
        }

        startIndex = endIndex;

        //must do a deep delete
        delete [] temp;
    }

}

//partition for interger quickSort
int SortingCompetition::partitionLength(char**& wordsLength, int left, int right)
{

    int pivot = strlen(wordsLength[right]);

    while ( left < right )
    {
        while (strlen(wordsLength[left]) < pivot )
            left++;

        while (strlen(wordsLength[right]) > pivot )
            right--;

        if (strlen(wordsLength[left]) == strlen(wordsLength[right]))
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
        //while (wordsAlpha[left] < pivot )
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
