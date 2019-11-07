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

void Window::pairStudent(Student* st, unsigned int timeEntered)
{
    studentAtWindow = st;
    studentAtWindow->timeEntered = timeEntered;
    isOpen = false;
}
