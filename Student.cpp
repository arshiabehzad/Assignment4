#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

Student::Student()
{

}

//overload constructor that takes in timeNeeded and timeEntered
Student::Student(unsigned int timeNeeded, unsigned int timeEnteredQueue)
{
    this->timeNeeded = timeNeeded;
    this->timeEnteredQueue = timeEnteredQueue;
}

//overload constructor that takes in waitTime (used in calculating median)
Student::Student(unsigned int waitTime)
{
    this->waitTime = waitTime;
}

Student::~Student()
{

}

