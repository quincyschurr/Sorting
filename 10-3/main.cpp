#include <iostream>
#include "person.h"
#include <chrono>
#include <ctime>

using namespace std;

int main()
{
    string name = "Quincy";
    int age = 19;

    char * name2 = "Jake";
    int * age2 = new int(18);
    //age2 = 18;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    Person *p1 = new Person(name, age);
    cout << p1->getName() << endl;
    cout << p1->getAge() << endl;
    end = chrono::system_clock::now();
    chrono::duration<double> elapsedSeconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "finished computation at " << ctime(&end_time)
         << "elapsed time: " << elapsedSeconds.count() << "s\n";

    chrono::time_point<chrono::system_clock> start2, end2;
    start = chrono::system_clock::now();
    Person *p2 = new Person(name2, age2);
    cout << p2->getName() << endl;
    cout << p2->getAge() << endl;
    end2 = chrono::system_clock::now();
    chrono::duration<double> elapsedSeconds2 = end2 - start2;
    time_t end_time2 = chrono::system_clock::to_time_t(end2);
    cout << "finished computation at " << ctime(&end_time2)
         << "elapsed time: " << elapsedSeconds2.count() << "s\n";
    //Person *p2 = new Person(name2, age2);

    return 0;
}

