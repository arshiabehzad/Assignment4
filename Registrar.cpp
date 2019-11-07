#include <iostream>
#include <fstream>
#include <cstddef>
#include "Registrar.h"

using namespace std;

Registrar::Registrar()
{
    time = 0;
}

Registrar::Registrar(string filename)
{
    time = 0;

    completedStudents = new DoubleLinkedList<Student*>();
    waitLine = new GenQueue<Student*>();
    readFile(filename);
}

void Registrar::readFile(string filename)
{
    fileLines = new GenQueue<int>;
    ifstream file;
    file.open(filename);
    string line;
    while (getline(file, line))
    {
        fileLines->insert(stoi(line));
    }
    windowsOpen = fileLines->remove();
    windowArray = new Window[windowsOpen];
    file.close();

}

void Registrar::nextTime()
{
    // checks if student is done 
    for (int i = 0; i < windowsOpen; i++)
    {
        //cout << "i: " <<i <<endl;
        if (windowArray[i].isOpen == true)
        {
            continue;
        }
        if (windowArray[i].studentAtWindow->timeNeeded ==  time - windowArray[i].studentAtWindow->timeEntered )
        {
            //cout << "works" << endl;
            completedStudents->insertBack(windowArray[i].studentAtWindow);
            //cout << "works2" << endl;
            windowArray[i].studentAtWindow = NULL;
            windowArray[i].isOpen = true;
        }
    }
    // adds student to queue 
    if (fileLines->isEmpty()== false)
    {
        if (time == fileLines->peek())
        {
            fileLines->remove();
            unsigned int studentsToAdd = fileLines->remove();
            cout << "# of Students to Add:" << studentsToAdd << endl;
            cout << "Student times to add: ";
            for (int i = 0; i < studentsToAdd; i++)
            {
                Student * st = new Student(fileLines->remove(),time);
                waitLine->insert(st);
                cout << st->timeNeeded << ", ";
            }
            cout << endl;
        }
    }
    //checks if windows are open and pairs student if its open
    for (int i = 0; i < windowsOpen; i++)
    {
        if (waitLine->isEmpty())
        {
            break;
        } 
        if (windowArray[i].isOpen)
        {
            Student * st = waitLine->remove();
            windowArray[i].pairStudent(st, time);
        }
    }
    //updates idle time of windows
    for (int i = 0; i < windowsOpen; i++)
    {
        if (windowArray[i].isOpen)
        {
            windowArray[i].timeIdle++;
        }
    }
    cout << endl;
    time++;
   
}

double Registrar::calculateMeanWaitTime()
{
    unsigned int sum = 0;
    ListNode<Student*> *curr = completedStudents->front;
    
    while (curr->next != NULL)
    {
        curr = curr->next; 
        sum+= curr->data->timeEntered - curr->data->timeEnteredQueue;
    }
    double mean = (double)sum/(double)completedStudents->getSize();
    return mean;
}

int Registrar::calculateLongestWaitTime()
{
    unsigned int max = 0;
    ListNode<Student *> *curr = completedStudents->front;
    while (curr != NULL)
    {
        unsigned int waitTime = curr->data->timeEntered - curr->data->timeEnteredQueue;
        //cout <<"Wait Time: " << waitTime << endl;
        if (waitTime > max)
        {
            //cout << "Max: " << max << endl;
            max = waitTime;
        }
        curr = curr->next;
    }
    return max;
}

int Registrar::calculateLongestTimeIdle()
{
    int max = 0;
    for (int i = 0; i < windowsOpen; i++)
    {
        if (windowArray[i].timeIdle > max)
            max = windowArray[i].timeIdle;
    }
    return max;
}

int Registrar::calculateStudentsOverTen()
{
    int counter = 0;
    ListNode<Student *> *curr = completedStudents->front;
    while (curr != NULL)
    {
        unsigned int waitTime = curr->data->timeEntered - curr->data->timeEnteredQueue;
        //cout <<"Wait Time: " << waitTime << endl;
        if (waitTime > 10)
        {
            counter++;
        }
        curr = curr->next;
    }
    return counter;
}

int Registrar::calculateWindowsOverFive()
{
    int counter = 0;
    for (int i = 0; i < windowsOpen; i++)
    {
        if (windowArray[i].timeIdle > 5)
            counter++;
    }
    return counter;
}

double Registrar::calculateMeanTimeIdle()
{
    int sum = 0;
    for(int i = 0; i < windowsOpen; i++ )
    {
        sum += windowArray[i].timeIdle;
    }
    return (double)sum/(double)windowsOpen;
}

double Registrar::calculateMedianWaitTime()
{
    unsigned int max = 0;;
    ListNode<Student *> *curr = completedStudents->front;
    int *waitTimesSorted = new int[completedStudents->getSize()];
    int *waitTimes = new int[completedStudents->getSize()];
    unsigned int arraySize = completedStudents->getSize();
    int index = 0;
    while (curr != NULL)
    {
        unsigned int waitTime = curr->data->timeEntered - curr->data->timeEnteredQueue;
        //cout <<"Wait Time: " << waitTime << endl;
        if (waitTime > max)
        {
            //cout << "Max: " << max << endl;
            max = waitTime;
        }
        waitTimes[index] = waitTime;
        curr = curr->next;
        index++;
    }
    //cout << "Max: " << max <<endl;
    unsigned int min = max;
    int indexOfMin = 0;
    for (int i = 0; i < arraySize; i++)
    {
        for (int j = 0; j < arraySize; j++)
        {
            //cout << "Min: " << min << endl;
            //cout <<endl;
            if (waitTimes[j] != -1)
            {
                if (waitTimes[j] < min )
                {
                    min = waitTimes[j];
                    indexOfMin = j;
                    //cout << "MinWorks: " << min << endl;;
                }
            }
        }
        //cout << "works" << endl;
        waitTimesSorted[i] = min;
        waitTimes[indexOfMin] = -1;
        min = max;
    }

    /*for (int i =0; i < arraySize; i++)
    {
        cout << waitTimesSorted[i] << ", ";
    }
    cout<<endl;*/

    //if array has an odd number of entries
    if (arraySize % 2 > 0)
    {
        return waitTimesSorted[arraySize / 2];
    }
    //else if array has a even number of entries
    double median = ((double)waitTimesSorted[arraySize / 2] + (double)waitTimesSorted[(arraySize / 2) - 1]) / 2.0;
    return median;
}

bool Registrar::windowArrayIsEmpty()
{
    for(int i = 0; i < windowsOpen; i++)
    {
        if(!windowArray[i].isOpen)
            return false;
    }
    return true;
}

void Registrar::printWindowsArray()
{
    cout << "Time: " << time << endl;
    for(int i = 0; i < windowsOpen; i++)
    {
        if (windowArray[i].isOpen == false)
        {
           //cout << time - windowArray[i].studentAtWindow->timeEntered  << ", ";
           cout << windowArray[i].studentAtWindow->timeNeeded << ":" << time - windowArray[i].studentAtWindow->timeEntered << ", ";
        }
        else
            cout << "open, ";
    }
    cout << endl;
    cout <<endl;
}

//prints wait line (note makes waitline empty)
void Registrar::printWaitLine()
{
    cout << "Wait Line: ";
    while (waitLine->isEmpty() == false)
        cout << waitLine->remove()->timeNeeded << ", " ;
    cout <<endl;
}

//prints file line (note makes file line empty)
void Registrar::printFileLine()
{
    cout << "File Line: ";
    while (fileLines->isEmpty() == false)
        cout << fileLines->remove()<< ", " ;
    cout <<endl;
}

