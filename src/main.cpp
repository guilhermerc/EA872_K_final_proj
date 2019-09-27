#include <iostream>
#include <ncurses.h>
#include <thread>

#include "screen.hpp"

using namespace std;

int main()
{
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);

    // I saw something about using these global variables, but they just don't
    // work
    // cout << "LINES: " << LINES << endl;
    // cout << "COLS:  " << COLS << endl;

    screen->init();
    screen->debug();
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    screen->stop();

    return 0;
}
