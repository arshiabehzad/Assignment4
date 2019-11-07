#include <iostream>
#include <fstream>
#include <cstddef>
#include "Registrar.h"

using namespace std;

//default constructor
Registrar::Registrar()
{
    time = 0;
}

//overload constructor that takes in filename
Registrar::Registrar(string filename)
{
    time = 0;

    completedStudents = new DoubleLinkedList<Student *>();
    waitLine = new GenQueue<Student *>();
    //calls read file passing in the file name
    readFile(filename);
}

//reads the file and adds the file
void Registrar::readFile(string filename)
{
    fileLines = new GenQueue<int>;
    ifstream file;
    file.open(filename);
    string line;
    // goes through the file
    while (getline(file, line))
    {
        //adds each line of the file to the fileLines queue;
        fileLines->insert(stoi(line));
    }
    //windowsOpen is basically the length of the array (the number of windows open to be used)
    windowsOpen = fileLines->remove();
    windowArray = new Window[windowsOpen];
    file.close();
}

//processes one minute passing
void Registrar::nextTime()
{
    // this section checks if student is done
    for (int i = 0; i < windowsOpen; i++)
    {
        /*if the windows is open continues on because it does not need to check if the student is done since
        there is no students*/
        if (windowArray[i].isOpen == true)
        {
            continue;
        }
        /*simple calculation to check if the students tiem is up based on the current time, time he entered
        the window and time he needed at the window*/
        if (windowArray[i].studentAtWindow->timeNeeded == time - windowArray[i].studentAtWindow->timeEntered)
        {
            //adds student to completedStudents linked list to be used later to generate stats
            completedStudents->insertBack(windowArray[i].studentAtWindow);
            //resets the window to empty
            windowArray[i].studentAtWindow = NULL;
            windowArray[i].isOpen = true;
        }
    }
    // this section adds student to queue
    if (fileLines->isEmpty() == false)
    {
        //checks if the current time is the time that students are to be added to the wait line queue 
        if (time == fileLines->peek())
        {
            //removes the time to be added from the file queue
            fileLines->remove();
            //gets how many students are going to be added to the queue based on the fileLines queue 
            unsigned int studentsToAdd = fileLines->remove();
            cout << "# of Students to Add:" << studentsToAdd << endl;
            cout << "Student times to add: ";
            //adds students to the queue
            for (int i = 0; i < studentsToAdd; i++)
            {
                //cretesa and new student to queue passing in the time needed and the time they entered the queue 
                Student *st = new Student(fileLines->remove(), time);
                waitLine->insert(st);
                cout << st->timeNeeded << ", ";
            }
            cout << endl;
        }
    }
    //this section checks if windows are open and pairs student if its open
    for (int i = 0; i < windowsOpen; i++)
    {
        //if the waitline is empty we will not be adding anymore students so we break the loop
        if (waitLine->isEmpty())
        {
            break;
        }
        //if the window is open pairs the student to the window
        if (windowArray[i].isOpen)
        {
            // removes it from the wait line queue
            Student *st = waitLine->remove();
            //pairs student to the window
            windowArray[i].pairStudent(st, time);
        }
    }
    //this section updates idle time of windows
    for (int i = 0; i < windowsOpen; i++)
    {
        //if the window is open after all of the processing above it will increment by 1 the idle time
        if (windowArray[i].isOpen)
        {
            windowArray[i].timeIdle++;
        }
    }
    cout << endl;
    //increments time by 1
    time++;
}

//goes through the double linked list of completed students and adds it to the list 
double Registrar::calculateMeanWaitTime()
{
    unsigned int sum = 0;
    ListNode<Student *> *curr = completedStudents->front;

    while (curr->next != NULL)
    {
        //indexes through the list
        curr = curr->next;
        //adds sum of time waited of each student
        sum += curr->data->timeEntered - curr->data->timeEnteredQueue;
    }
    //calculates mean
    double mean = (double)sum / (double)completedStudents->getSize();
    return mean;
}

//goes through the double linked list of completed students and finds the longest wait time
int Registrar::calculateLongestWaitTime()
{
    //max variable that will be the largest element in list by the end of the loop
    unsigned int max = 0;
    ListNode<Student *> *curr = completedStudents->front;
    while (curr != NULL)
    {
        //calculates wait time of each student
        unsigned int waitTime = curr->data->timeEntered - curr->data->timeEnteredQueue;
        //cout <<"Wait Time: " << waitTime << endl;
        if (waitTime > max)
        {
            //cout << "Max: " << max << endl;
            max = waitTime;
        }
        //indexes through the list
        curr = curr->next;
    }
    return max;
}

//goes through the window array and finds the longest window idle time 
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

//goes through the double linked list of completed students and finds the number of students that waited over ten minues
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
            //if larger than 10 adds to the counter
            counter++;
        }
        //indexes through the list
        curr = curr->next;
    }
    return counter;
}

//goes through the window array and finds the windows that were idle for longer than 5 minutes
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

//goes through the window array and calculates the mean of the window idle times
double Registrar::calculateMeanTimeIdle()
{
    int sum = 0;
    for (int i = 0; i < windowsOpen; i++)
    {
        sum += windowArray[i].timeIdle;
    }
    return (double)sum / (double)windowsOpen;
}

/*goes through the double linked list of completed students calculates mean wait time
 In this method there are 4 major steps:
    1. Find the max of the list in order to set the min equal to it later on
    2. Copy the contents of the completed students list to an array of ints of their wait times 
       (happens in same for loop as step 1)
    3. Sort the new array of wait times into a new array*
    4. Calculte the median based on the new sorted array  
    
    *Probably not the most effiecient sort method but I made it myself and it works :)*/
double Registrar::calculateMedianWaitTime()
{

    unsigned int max = 0;
    ListNode<Student *> *curr = completedStudents->front;
    int *waitTimesSorted = new int[completedStudents->getSize()];
    int *waitTimes = new int[completedStudents->getSize()];
    unsigned int arraySize = completedStudents->getSize();
    int index = 0;
    //step 1 and 2
    while (curr != NULL)
    {
        unsigned int waitTime = curr->data->timeEntered - curr->data->timeEnteredQueue;
        //step 1
        if (waitTime > max)
        {
            max = waitTime;
        }
        //step 2
        waitTimes[index] = waitTime;
        curr = curr->next;
        index++;
    }
    unsigned int min = max;
    int indexOfMin = 0;
    //step 3
    for (int i = 0; i < arraySize; i++)
    {
        //calculates min NOT INClUDING previous mins
        for (int j = 0; j < arraySize; j++)
        {
            if (waitTimes[j] != -1)
            {
                if (waitTimes[j] < min)
                {
                    min = waitTimes[j];
                    indexOfMin = j;
                }
            }
        }
        //adds the next lowest number to the array 
        waitTimesSorted[i] = min;
        //ensures this min wont be counted again
        waitTimes[indexOfMin] = -1;
        //resets min to be used again 
        min = max;
    }

    //if array has an odd number of entries
    if (arraySize % 2 > 0)
    {
        return waitTimesSorted[arraySize / 2];
    }
    //else if array has a even number of entries
    double median = ((double)waitTimesSorted[arraySize / 2] + (double)waitTimesSorted[(arraySize / 2) - 1]) / 2.0;
    return median;
}

//checks if the window array is empty
bool Registrar::windowArrayIsEmpty()
{
    for (int i = 0; i < windowsOpen; i++)
    {
        if (!windowArray[i].isOpen)
            return false;
    }
    return true;
}

//prints out windows array
void Registrar::printWindowsArray()
{
    cout << "Time: " << time << endl;
    for (int i = 0; i < windowsOpen; i++)
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
    cout << endl;
}

//prints wait line (note makes waitline empty)
void Registrar::printWaitLine()
{
    cout << "Wait Line: ";
    while (waitLine->isEmpty() == false)
        cout << waitLine->remove()->timeNeeded << ", ";
    cout << endl;
}

//prints file line (note makes file line empty)
void Registrar::printFileLine()
{
    cout << "File Line: ";
    while (fileLines->isEmpty() == false)
        cout << fileLines->remove() << ", ";
    cout << endl;
}
