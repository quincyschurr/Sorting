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
