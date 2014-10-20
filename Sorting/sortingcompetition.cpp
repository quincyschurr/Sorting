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
    delete [] temp;
    delete[] wordsLength;
    delete [] lengths;
    delete [] tempL;

    fout.close();
}

bool SortingCompetition::prepareData()
{
    //declare new char** to copy the read data into
    //counter is = to number of words read in.

    temp = new char*[counter];
    wordsLength = new char*[counter];
    lengths = new int[counter];
    tempL = new int[counter];


    //copying values into the copy arrays
    for(int j = 0; j < counter; j++)
    {
        wordsLength[j] = words[j];
    }

    //filling array with string lengths of each word
    for(int i = 0; i < counter; i++)
    {
        lengths[i] = strlen(words[i]);
    }

    return true;
}

bool SortingCompetition::readData()
{

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
        buffer = new char[temporary.size() + 1];//accounts for the null terminator of the phrase
        strcpy(buffer, temporary.c_str());

        //put the buffer in a vector of char*
        wordsVector.push_back(buffer);
    }

    counter = wordsVector.size();

    words = new char*[counter];

    for(int i = 0; i < counter; i++)
    {
        words[i] = wordsVector[i];
    }

    fin.close();
    return true;
}

void SortingCompetition::setFileName(const string& inputFileName)
{
    input = inputFileName.c_str();
}

void SortingCompetition::sortData()
{

    //left is the first element of array and right is the final element
    int left = 0;
    int right = counter - 1;

    //mergesort(wordsLength, left, right);
    mergesort(wordsLength, lengths, left, right); //fastest one
    //quickSortLength(wordsLength, lengths, left, right);
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
    //int pivot = medianof5(wordsLength, left, right); //median of 5 pivot
    int pivot = strlen(wordsLength[right]);

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

    //pivot is just the last element
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

void SortingCompetition::lengthAlpha2(char**& wordsLength)
{

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
        mergesortAlpha(temp, 0, lengthCount -1);
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

int SortingCompetition::medianof5(int * lengths, int left, int right)
{
    int mid = (left + right)/2;
    int leftmid = (left + mid)/2;
    int rightmid = (mid + right)/2;
    int median = lengths[left] + lengths[leftmid] + lengths[mid] + lengths[rightmid] + lengths[right];
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
    delete[] medianTemp;

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
    delete[] medianTemp;
}

//void SortingCompetition::mergesort(char**& words, int left, int right, int cap, bool(*comparisonFunction)(char*, char*));

/*void SortingCompetition::mergesort(char**& words, int left, int right)
{
    int mid;
    if (left < right)
    {
        mid=(left + right)/2;
        mergesort(words, left, mid);
        mergesort(words, mid+1, right);
        merge(words, left, right, mid);
    }
    return;
}*/

void SortingCompetition::merge(char**& words, int left, int right, int mid)
{
    //char** temp = new char*[cap];
    int i = left;
    int k = left;
    int j = mid + 1;

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

void SortingCompetition::mergesortAlpha(char**& words, int left, int right)
{
    int mid;
    if (left < right)
    {
        mid=(left + right)/2;
        mergesortAlpha(words, left, mid);
        mergesortAlpha(words, mid+1, right);
        mergeAlpha(words, left, right, mid);
    }
    return;
}

void SortingCompetition::mergeAlpha(char**& words, int left, int right, int mid)
{
    //char** temp = new char*[cap];
    int i = left;
    int k = left;
    int j = mid + 1;

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

void SortingCompetition::mergesort(char**& words, int * &lengths, int left, int right)
{
    int mid;
    if (left < right)
    {
        mid=(left + right)/2;
        mergesort(words, lengths, left, mid);
        mergesort(words, lengths, mid+1, right);
        merge(words, lengths, left, right, mid);
    }
    return;
}

void SortingCompetition::merge(char**& words, int * &lengths, int left, int right, int mid)
{
    //char** temp = new char*[cap];
    int i = left;
    int k = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        //if (strlen(words[i]) < strlen(words[j]))
        if(lengths[i] < lengths[j])
        {
            temp[k] = words[i];
            tempL[k] = lengths[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = words[j];
            tempL[k] = lengths[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = words[i];
        tempL[k] = lengths[i];
        k++;
        i++;
    }
    while (j <= right)
    {
        temp[k] = words[j];
        tempL[k] = lengths[j];
        k++;
        j++;
    }
    for (i = left; i < k; i++)
    {
        words[i] = temp[i];
        lengths[i] = tempL[i];
    }
}

void SortingCompetition::quickSortLength(char**& wordsLength, int * &lengths, int left, int right)
{
    //calls quickSortLength recursively to sort by length
    if ( left < right )
    {
        int mid = 0;
        mid = partitionLength(wordsLength, lengths, left, right);
        quickSortLength(wordsLength, lengths, left, mid-1);
        quickSortLength(wordsLength, lengths, mid+1, right);
    }
}

//partition for interger quickSort
int SortingCompetition::partitionLength(char**& wordsLength, int * &lengths, int left, int right)
{

    //int pivot = findMedianLength(wordsLength, left, right);//with median of 3 pivot
    int pivot = medianof5(lengths, left, right); //median of 5 pivot

    while ( left < right )
    {
        while (lengths[left] < pivot )
        {
            left++;//moves pointer
        }

        while (lengths[right] > pivot )
        {
            right--;//moves pointer
        }

        if (lengths[left] == lengths[right])
        {
            left++;//will increase pointer by one
        }

        else if ( left < right )
        {
            swap(wordsLength[left], wordsLength[right]);
            swap(lengths[left], lengths[right]);

            //this runs slower
            /*char* temp = wordsLength[left];
            wordsLength[left] = wordsLength[right];
            wordsLength[right] = temp;*/
        }
    }

    return right;
}


SortingCompetition::~SortingCompetition()
{

}
