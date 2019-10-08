#include <thread>
#include <ncurses.h>

#include "keyboard_func.hpp"

void keyboard_func(char * last_key, bool * processed, bool * running)
{
    char c;
    while((*running) == true)
    {
        if((*processed) == true)
        {
            c = getch();
            if(c != ERR)
            {
                (*last_key) = c;
                (*processed) = false;
            }
            else
                (*last_key) = 0;
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
    return;
}
