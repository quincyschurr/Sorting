#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iomanip>

using namespace std;
class Person
{
private:
    string name;
    int age;
public:
    Person();
    Person(string, int);
    Person(char* &, int* &);
    ~Person();
    string getName();
    void setName(string);
    int getAge();
    void setAge(int);
};

#endif // PERSON_H
