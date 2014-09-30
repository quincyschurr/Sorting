#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H

class SortingCompetition
{
private:


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
