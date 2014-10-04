#include "person.h"

Person::Person()
{

}

Person::Person(string name, int age) {
    this->name = name;
    this->age = age;
}

Person::Person(char* &name, int* &age) {
    this->name = name;
    this->age = *age;
}

Person::~Person() {

}

string Person::getName() {
    return name;
}

void Person::setName(string name) {
    name = name;
}

int Person::getAge() {
    return age;
}

void Person::setAge(int age) {
    age = age;
}
