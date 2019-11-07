#pragma once
#include "Student.h"

using namespace std;

class Window
{
    public:
        Window();
        ~Window();
    
        Student *studentAtWindow;
        bool isOpen;

        unsigned int timeIdle;

        void pairStudent(Student* st, unsigned int timeEntered);
};