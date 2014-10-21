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
    //sets input file name
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

    //out puts sorted words
    for(int i = 0; i < counter; i++)
    {
        fout << wordsLength[i] << endl;
    }
    fout << endl;
    fout << "*****END OF OUTPUT*****" << endl;

    //deep delete for wordsLength
    for(int h = 0; h < counter; h++)
    {
        delete wordsLength[h];
    }

    //deletes for all arrays used
    delete[] words;
    delete [] temp;
    delete[] wordsLength;
    delete [] lengths;
    delete [] tempL;

    fout.close();
}

bool SortingCompetition::prepareData()
{
    //allocates a temp array used later in sorting
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

    for(int i = 0; i < counter; i++) //changes from vector to array
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

    mergesort(wordsLength, lengths, left, right);
    lengthAlpha2(wordsLength);

}
//sorts each length alphabetically
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
            if(i != strlen(wordsLength[x])) //break loop if string lengths don't match up
            {
                break;
            }

            else //iterates counters
            {
                lengthCount++;
                x++;
                endIndex++;
            }
        }

        x = startIndex;
        char ** temp = new char*[lengthCount];
        //assigns temp to wordsLength array
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
        //breaks loop if the last word tested is the biggest length
        if(strlen(wordsLength[endIndex]) == longestWord)
        {
            break;
        }

    }
}

void SortingCompetition::mergesortAlpha(char**& words, int left, int right)
{
    int mid;
    //recursive mergesort if left iterator is less than right
    if (left < right)
    {
        mid=(left + right)/2;
        mergesortAlpha(words, left, mid); //sorts left side
        mergesortAlpha(words, mid+1, right); //sorts right side
        mergeAlpha(words, left, right, mid); //combines sorted arrays
    }
    return;
}

void SortingCompetition::mergeAlpha(char**& words, int left, int right, int mid)
{
    //iterators
    int i = left;
    int k = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (strcmp(words[i], words[j]) <= -1) //if words[i] is less alphabetically than words[j]
        {
            temp[k] = words[i]; //fills temp with words on left side
            k++;
            i++;
        }
        else
        {
            temp[k] = words[j]; //if words are higher alphabetically, fills temp with right side
            k++;
            j++;
        }
    }
    while (i <= mid)
    {//meges left side
        temp[k] = words[i];
        k++;
        i++;
    }
    while (j <= right)
    {//merges right side
        temp[k] = words[j];
        k++;
        j++;
    }
    for (i = left; i < k; i++)
    {
        words[i] = temp[i]; //sorts
    }
}

void SortingCompetition::mergesort(char**& words, int * &lengths, int left, int right)
{
    int mid;
    if (left < right)
    {
        mid=(left + right)/2;
        mergesort(words, lengths, left, mid); //sorts left array
        mergesort(words, lengths, mid+1, right); //sorts right array
        merge(words, lengths, left, right, mid); //merges sorted arrays
    }
    return;
}

void SortingCompetition::merge(char**& words, int * &lengths, int left, int right, int mid)
{
    //iterators
    int i = left;
    int k = left;
    int j = mid + 1;

    while (i <= mid && j <= right) //loops while left itarator is less than middle
    {                              //and while middle iterator is less than right
        //if (strlen(words[i]) < strlen(words[j]))
        if(lengths[i] < lengths[j]) //uses a temp to sort
        {
            temp[k] = words[i]; //fills temp if left side is less than right
            tempL[k] = lengths[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = words[j]; //fills temp if rights less than left
            tempL[k] = lengths[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        temp[k] = words[i]; //iterates and makes fills temp with words
        tempL[k] = lengths[i];
        k++;
        i++;
    }
    while (j <= right)
    {
        temp[k] = words[j]; //iterates j until it reaches right and fills temp
        tempL[k] = lengths[j];
        k++;
        j++;
    }
    for (i = left; i < k; i++)
    {
        words[i] = temp[i]; //puts temps in words
        lengths[i] = tempL[i];
    }
}

SortingCompetition::~SortingCompetition()
{

}
