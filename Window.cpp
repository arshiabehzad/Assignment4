#include "Window.h"
#include <cstddef>
using namespace std;

Window::Window()
{
    isOpen = true;
    studentAtWindow = NULL;
    timeIdle = 0;
}

Window::~Window()
{

}

//pairs student to an instance variable, and sets the window being open to false
void Window::pairStudent(Student* st, unsigned int timeEntered)
{
    studentAtWindow = st;
    studentAtWindow->timeEntered = timeEntered;
    isOpen = false;
}
