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

    fout << "*****STARTING OUTPUT*****" << endl;

    for(int i = 0; i < counter; i++)
    {
        fout << wordsLength[i] << endl;
    }
    fout << endl;
    fout << "*****END OF OUTPUT*****" << endl;

    for(int h = 0; h < counter; h++)
    {
        delete wordsLength[h];
    }

    delete[] words;
    delete[] wordsLength;

    fout.close();
}

bool SortingCompetition::prepareData()
{
    //declare new char** to copy the read data into
    //counter is = to number of words read in.

    wordsLength = new char*[counter];

    cout << "This is executing in prepareData " << endl;

    //copying values into the copy arrays
    for(int j = 0; j < counter; j++)
    {
        wordsLength[j] = words[j];
    }

    return true;
}

bool SortingCompetition::readData()
{
    cout << "This is the beginning of readData" << endl;

    string temporary;
    char* buffer;

    //need to change this so that we use the getFilename function.
    ifstream fin(this->input.c_str());//add a file to read in

    if(!fin)
    {
        cerr << "This file could not be opened" << endl;
        exit(1);
    }

    while(!fin.eof())
    {
        fin >> temporary;
        buffer = new char[temporary.length() + 1];//accounts for the null terminator of the phrase
        memset(buffer, 0, (temporary.length() + 1) * sizeof(char));//initalize buffer to 0 so no random characters

        //this will get each character and add it to the bugger
        for(int k = 0; k < temporary.length(); k++)
        {
            buffer[k] = temporary[k];
        }

        //put the buffer in a vector of char*
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
}

void SortingCompetition::sortData()
{
    cout << "This is executing in sortData" << endl;

    //left is the first element of array and right is the final element
    int left = 0;
    int right = counter - 1;

    mergesort(wordsLength, left, right, counter);
    //quickSortLength(wordsLength, left, right);
    //quickSortTest(wordsCopy, left, right);
    lengthAlpha2(wordsLength);

}

//quick sort with integers
void SortingCompetition::quickSortLength(char**& wordsLength, int left, int right)
{
    //calls quickSortLength recursively to sort by length
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

    //int pivot = findMedianLength(wordsLength, left, right);//with median of 3 pivot
    int pivot = medianof5(wordsLength, left, right); //median of 5 pivot

    while ( left < right )
    {
        while (strlen(wordsLength[left]) < pivot )
        {
            left++;//moves pointer
        }

        while (strlen(wordsLength[right]) > pivot )
        {
            right--;//moves pointer
        }

        if (strlen(wordsLength[left]) == strlen(wordsLength[right]))
        {
            left++;//will increase pointer by one
        }

        else if ( left < right )
        {
            swap(wordsLength[left], wordsLength[right]);

            //this runs slower
            /*char* temp = wordsLength[left];
            wordsLength[left] = wordsLength[right];
            wordsLength[right] = temp;*/
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
    //median pivot function calls
    char* pivot = medianof5alpha(wordsAlpha, left, right);
    //char* pivot = findMedianAlpha(wordsAlpha, left, right);

    //pivot is now just the last element
    //char* pivot = wordsAlpha[right];

    while ( left < right )
    {
        //while (wordsAlpha[left] < pivot )
        //while(wordsAlpha[left][0] < pivot)
        while(strcmp(wordsAlpha[left], pivot) <= -1)
        {
            left++;
        }

        //while (wordsAlpha[right] > pivot)
        //while(wordsAlpha[right][0] > pivot)
        while(strcmp(wordsAlpha[right], pivot) >= 1)
        {
            right--;
        }

        //if ( strlen(wordsAlpha[left] == strlen(wordsAlpha[right]) )
        if(strcmp(wordsAlpha[left], wordsAlpha[right]) == 0)
        {
            left++;
        }
        else if ( left < right )
        {
            swap(wordsAlpha[left], wordsAlpha[right]);
            /*char* temp = wordsAlpha[left];
            wordsAlpha[left] = wordsAlpha[right];
            wordsAlpha[right] = temp;*/
        }
    }

    return right;

}

void SortingCompetition::lengthAlpha2(char **& wordsLength)
{

    //cout << "ENTERING lengthAlpha" << endl;

    int longestWord = strlen(wordsLength[counter - 1]);
    int startIndex = 0;
    int endIndex = 0;
    int lengthCount = 0;
    int x = 0; //iterator

    for(int i = 1; i <= longestWord; i++)
    { //iterates for each size of word

        x = startIndex;
        lengthCount = 0;//must make this zero for each loop so we add how many words of a certain length there are

        while(true)
        {
            if(i != strlen(wordsLength[x]))
            {
                break;
            }
            else
            {
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

        //pass temp into alpha sort
        mergesortAlpha(temp, 0, lengthCount -1, lengthCount);
        x = startIndex;

        //place the sorted temp array back into correct elements in array
        for(int j = 0; j < lengthCount; j++)
        {
            wordsLength[x] = temp[j];
            x++;
        }

        startIndex = endIndex;

        delete [] temp;

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

char* SortingCompetition::medianof5alpha(char** words, int left, int right)
{
    int median = 0;
    int m = 0;
    int mid = (left + right)/2;
    int leftmid = (left + mid)/2;
    int rightmid = (mid + right)/2;
    /*int l = words[left][0];
    int lm = words[leftmid][0];
    int m = words[mid][0];
    int rm = words[rightmid][0];
    int r = words[right][0];*/

    m = (left + leftmid + mid + rightmid + right)/5;
    median = m;

    char* medianTemp = new char[m];
    medianTemp = words[m];

    return medianTemp;

}

int SortingCompetition::findMedianLength(char** words, int left, int right)
{
    int mid = (left + right)/2;
    int median = strlen(words[left]) + strlen(words[right]) + strlen(words[mid]);
    median = median/3;
    return median;
}

//finds median by comparing leading chars by using median of three
char* SortingCompetition::findMedianAlpha(char ** words, int left, int right)
{
    int m = 0;
    int median = 0;
    int mid = (left + right)/2;
    /*int l = words[left][0];
    int r = words[right][0];
    int m = words[mid][0];*/
    m = (left + right + mid)/3;
    median = m;

    char* medianTemp = new char[m];
    medianTemp = words[m];

    //we want to return a char* that contains the word that will act as a pivot
    return medianTemp;
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

void SortingCompetition::mergesort(char ** words, int left, int right, int cap)
{
    int mid;
    if (left < right)
    {
        mid=(left + right)/2;
        mergesort(words, left, mid, cap);
        mergesort(words, mid+1, right, cap);
        merge(words, left, right, mid, cap);
    }
    return;
}

void SortingCompetition::merge(char ** words, int left, int right, int mid, int cap)
{
    int i, j, k;
    char * temp[cap];
    i = left;
    k = left;
    j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (strlen(words[i]) < strlen(words[j]))
        {
            temp[k] = words[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = words[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = words[i];
        k++;
        i++;
    }
    while (j <= right)
    {
        temp[k] = words[j];
        k++;
        j++;
    }
    for (i = left; i < k; i++)
    {
        words[i] = temp[i];
    }
}

void SortingCompetition::mergesortAlpha(char ** words, int left, int right, int cap)
{
    int mid;
    if (left < right)
    {
        mid=(left + right)/2;
        mergesortAlpha(words, left, mid, cap);
        mergesortAlpha(words, mid+1, right, cap);
        mergeAlpha(words, left, right, mid, cap);
    }
    return;
}

void SortingCompetition::mergeAlpha(char ** words, int left, int right, int mid, int cap)
{
    int i, j, k;
    char * temp[cap];
    i = left;
    k = left;
    j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (strcmp(words[i], words[j]) <= -1)
        {
            temp[k] = words[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = words[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = words[i];
        k++;
        i++;
    }
    while (j <= right)
    {
        temp[k] = words[j];
        k++;
        j++;
    }
    for (i = left; i < k; i++)
    {
        words[i] = temp[i];
    }
}


SortingCompetition::~SortingCompetition()
{

}
