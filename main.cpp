#include "Registrar.h" 
using namespace std;

int main(int argc, char **argv)
{
    //gets command argument
    string filename = argv[1];
    Registrar* r = new Registrar(filename);
    /*loop will break if the waitLine queue is empty, the window array is empty, and the file lines queue is empty */
    while (r->waitLine->isEmpty() == false || r->windowArrayIsEmpty() == false || r->fileLines->isEmpty() == false)
    {
        r->printWindowsArray();
        r->nextTime();
    }
    //prints out stat
    cout << "Mean Wait Time: " << r->calculateMeanWaitTime() << endl;
    cout << "Median Wait Time: " << r->calculateMedianWaitTime() << endl;
    cout << "Longest Wait Time: " << r->calculateLongestWaitTime() << endl;
    cout << "Students Who Waited Over 10 Minutes: " << r->calculateStudentsOverTen() << endl;
    cout << "Mean Window Idle Time: " << r->calculateMeanTimeIdle() << endl;
    cout << "Longest Window Idle Time: " << r->calculateLongestTimeIdle() << endl;
    cout << "Windows Who Were Idle Over 5 Minutes: " << r->calculateWindowsOverFive() << endl;
}