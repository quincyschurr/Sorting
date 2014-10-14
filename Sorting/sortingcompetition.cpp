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
    ofstream fout("output.txt", ios::out);

    cout << "WE ARE GETTING TO THE OUTPUT METHOD" << endl;

    fout << "Prints sorted by length" << endl;
    for(int i = 0; i < counter; i++)
    {
        fout << wordsLength[i] << endl;
    }
    fout << endl << endl;

    //we have to go through and do a deep delete as well.
    //with a for loop

    delete[] words;
    delete[] wordsLength;
    delete[] wordsCopy;

    fout.close();
}

bool SortingCompetition::prepareData()
{
    //declare new char** to copy the read data into
    //counter is = to number of words read in.
    wordsLength = new char*[counter];
    wordsCopy = new char*[counter];

    cout << "This is executing in prepareData " << endl;

    //copying values into the copy arrays
    for(int j = 0; j < counter; j++)
    {
        wordsLength[j] = words[j];
        wordsCopy[j] = words[j];
    }

    return true;
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
    return true;
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
    //quickSortTest(wordsCopy, left, right);
    lengthAlpha2(wordsLength);


    //trying to test the median three pivot!!!
    //quickSortTest(wordsCopy, left, right);
}
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

    int pivot = findMedianLength(wordsLength, left, right);
    //int pivot = medianof5(wordsLength, left, right);

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
    //char pivot = findMedianAlpha(wordsAlpha, left, right);
    //will have to change pivot to &pivot in all strcmp
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


void SortingCompetition::lengthAlpha2(char **& wordsLength)
{

    int longestWord = strlen(wordsLength[counter - 1]);
    int startIndex = 0;
    int endIndex = 0;
    int lengthCount = 0;
    int x = 0; //iterator

    for(int i = 1; i <= longestWord; i++)
    { //iterates for each size of word

        x = startIndex;
        cout << startIndex << endl;
        lengthCount = 0;

        while(true)
        {
            if(i != strlen(wordsLength[x]))
            {
                break;
            }
            else {
                lengthCount++;
                x++;
                endIndex++;
            }
        }

        x = startIndex;
        char ** temp = new char*[lengthCount];
        for(int j = 0; j < lengthCount; j++)
        {
            temp[j] = wordsLength[x];
            x++;
        }
        quickSortAlpha(temp, 0, lengthCount -1);

        x = startIndex;
        for(int j = 0; j < lengthCount; j++)
        {
            wordsLength[x] = temp[j];
            x++;
        }
        startIndex = endIndex;
        //I changed this from endIndex-1 to endIndex, it seemed to work a bit better
        //but still has problems

        delete [] temp;

        //this ends the for loop and without it, it gets stuck in an infinite loop
        //or something like that
        if(strlen(wordsLength[endIndex]) == longestWord)
        {
            break;
        }

    }
}

int SortingCompetition::medianof5(char** words, int left, int right)
{
    int mid = (left + right)/2;
    int leftmid = (left + mid)/2;
    int rightmid = (mid + right)/2;
    int median = strlen(words[left]) + strlen(words[leftmid]) + strlen(words[mid]) + strlen(words[rightmid]) + strlen(words[right]);
    median = median/5;
    return median;
}

char SortingCompetition::medianof5alpha(char** words, int left, int right)
{
    char median = '0';
    int mid = (left + right)/2;
    int leftmid = (left + mid)/2;
    int rightmid = (mid + right)/2;
    int l = words[left][0];
    int lm = words[leftmid][0];
    int m = words[mid][0];
    int rm = words[rightmid][0];
    int r = words[right][0];

    m = (l + lm + m + rm + r)/5;
    median = (char)m;

    return median;

}

int SortingCompetition::findMedianLength(char** words, int left, int right)
{
    int mid = (left + right)/2;
    int median = strlen(words[left]) + strlen(words[right]) + strlen(words[mid]);
    median = median/3;
    return median;
}

//finds median by comparing leading chars by using median of three
char SortingCompetition::findMedianAlpha(char ** words, int left, int right)
{
    char median = '0';
    int mid = (left + right)/2;
    int l = words[left][0];
    int r = words[right][0];
    int m = words[mid][0];
    m = (l + r + m)/3;
    median = (char)m;

    return median;
}

//http://stackoverflow.com/questions/7559608/median-of-three-values-strategy-
//http://stackoverflow.com/questions/5666717/median-3-quick-sort-implementation

/*void SortingCompetition::quickSortTest(char**& wordsCopy, int left, int right)
{
    if ( left < right )
    {
        //I can't figure out why there is an error here...
        int pivot = ThreePivotLength(wordsCopy, left, right);
        quickSortTest(wordsCopy, left, pivot-1);
        quickSortTest(wordsCopy, pivot+1, right);
    }



}

//http://www.java2s.com/Code/Java/Collections-Data-Structure/Quicksortwithmedianofthreepartitioning.htm
int SortingCompetition::ThreePivotLength(char**& wordsCopy, int left, int right)
{
    //https://www.youtube.com/watch?v=6UHCG64tHgo (partition general method)
    //https://www.youtube.com/watch?v=gP1L5iVfdt0 (picking a pivot by random)

    int center = strlen(wordsCopy[right/2]);

    //this while loop is causing an infinite loop
    while(left <= (strlen(wordsCopy[center])) && right > (strlen(wordsCopy[center])))
    {//trying to make it so the pivot will be the biggest part of the partion
        //so if there are multiple strings with the same length the center value
        //will be at the highest end before length sort... if that makes sense

        if(strlen(wordsCopy[left]) > center)
        {
            swap(wordsCopy[left], wordsCopy[center]);
            left++;
        }

        if(strlen(wordsCopy[right]) <= strlen(wordsCopy[center]))
        {
            swap(wordsCopy[right], wordsCopy[center]);
            right--;
        }
    }

    return strlen(wordsCopy[center]);

}*/

SortingCompetition::~SortingCompetition()
{

}
