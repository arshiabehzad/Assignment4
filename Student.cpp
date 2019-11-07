#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

Student::Student()
{

}

Student::Student(unsigned int timeNeeded, unsigned int timeEnteredQueue)
{
    this->timeNeeded = timeNeeded;
    this->timeEnteredQueue = timeEnteredQueue;
}

Student::Student(unsigned int waitTime)
{
    this->waitTime = waitTime;
}

Student::~Student()
{

}

