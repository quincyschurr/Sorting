#include "sortingcompetition.h"
#include <iomanip>
#include <vector>

using namespace std;

SortingCompetition::SortingCompetition()
{


}

SortingCompetition::SortingCompetition(const string &inputFileName)
{

}

void SortingCompetition::outputData(const string& outputFileName)
{

}

bool SortingCompetition::prepareData()
{

}

bool SortingCompetition::readData()
{
    ifstream fin();//add a file to read in

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


    fin.getline(buffer, 81);

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
void SortingCompetition::quickSort(int *& num, int left, int right)
{
    if ( left < right )
    {
        int mid = SortingCompetition::partition(num, left, right);
        quickSort(num, left, mid-1);
        quickSort(num, mid+1, right);
    }
}
//partition for interger quickSort
int SortingCompetition::partition(int * &num, int left, int right)
{
    int pivot = num[right];

    while ( left < right )
    {
        while ( num[left] < pivot )
            left++;

        while ( num[right] > pivot )
            right--;

        if ( num[left] == num[right] )
            left++;
        else if ( left < right )
        {
            int temp = num[left];
            num[left] = num[right];
            num[right] = temp;
        }
    }

    return right;

}
