#pragma once
using namespace std;

class Student
{
    public:
        Student();
        Student(unsigned int timeNeeded, unsigned int timeEnteredQueue);
        Student(unsigned int waitTime);
        ~Student();
    
        unsigned int timeNeeded;
        unsigned int timeEntered;
        unsigned int timeEnteredQueue;
        unsigned int waitTime;
};