#pragma once
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include "DoubleLinkedList.h"

using namespace std;

class Registrar
{
    public:
        Registrar();
        Registrar(string filename);
        ~Registrar();

        void readFile(string filename);
        void nextTime();
        bool windowArrayIsEmpty();
        void printWindowsArray();
        void printWaitLine();
        void printFileLine();

        double calculateMeanWaitTime();
        double calculateMedianWaitTime();
        int calculateLongestWaitTime();
        int calculateLongestTimeIdle();
        int calculateStudentsOverTen();
        int calculateWindowsOverFive();
        double calculateMeanTimeIdle();

        unsigned int windowsOpen;
        unsigned int time;

        GenQueue <int>* fileLines;
        GenQueue <Student*>* waitLine;
        Window* windowArray;
        DoubleLinkedList <Student*>* completedStudents;
};