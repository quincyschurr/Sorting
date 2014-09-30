#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

#include <string>
#include <vector>

using namespace std;

class SortingCompetition
{
private:
    vector <string> words;
    const string inputFileName;

public:

    void outputData(const string& outputFileName);
    bool prepareData();
    bool readData();
    void setFileName(const string& inputFileName);
    void sortData();

    SortingCompetition();
    SortingCompetition(const string& inputFileName);
    ~SortingCompetition();

};

#endif // SORTINGCOMPETITION_H
