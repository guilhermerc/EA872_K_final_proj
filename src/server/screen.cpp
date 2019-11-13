#include <ncurses.h>

#include "screen.hpp"

using namespace View;

void Screen::set_resolution()
{
    resizeterm(this->height, this->width);
}

Screen::Screen(int height, int width)
{
    this->height = height;
    this->width = width;
};

Screen::~Screen()
{
    this->stop();
};

void Screen::init()
{
    initscr();              // Start curses mode

	start_color();			/* Start color 			*/

    this->set_resolution();
    raw();                  // Line buffering disabled
    curs_set(0);            // Do not display cursor
    noecho();               // Don't echo while we do 'getch()'
};

void Screen::stop()
{
    // TODO: Check exactly what it does
    endwin();
};
