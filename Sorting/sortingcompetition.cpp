#include "sortingcompetition.h"
#include <iomanip>
#include <vector>

using namespace std;

SortingCompetition::SortingCompetition()
{


}

SortingCompetition::SortingCompetition(const string &inputFileName)
{
    this->inputFileName = inputFileName;
}

void SortingCompetition::outputData(const string& outputFileName)
{

}

bool SortingCompetition::prepareData()
{

}

bool SortingCompetition::readData()
{

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
void SortingCompetition::quickSortLength(int *& num, int left, int right)
{
    if ( left < right )
    {
        int mid = SortingCompetition::partition(num, left, right);
        quickSortLength(num, left, mid-1);
        quickSortLength(num, mid+1, right);
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
