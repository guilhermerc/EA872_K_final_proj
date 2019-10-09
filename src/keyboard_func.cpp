#include <chrono>
#include <thread>
#include <ncurses.h>

#include "keyboard_func.hpp"

void keyboard_func(char * key, bool * processed, bool * running)
{
    char c;
    while((*running) == true)
    {
        // If the last character is already processed, then tries to read a new
        // one
        if((*processed) == true)
        {
            c = getch();
            if(c != ERR)
            {
                (*key) = c;
                (*processed) = false;
            }
            else
                (*key) = 0;
        }
        // TODO: Is this rate really necessary?
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
    return;
}
