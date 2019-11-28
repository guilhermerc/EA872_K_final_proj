#include <ncurses.h>

#include "screen.hpp"

using namespace View;

// CHECKED
void Screen::set_resolution()
{
    resizeterm(this->height, this->width);
}

// CHECKED
Screen::Screen(int height, int width)
{
    this->height = height;
    this->width = width;
};

// CHECKED
Screen::~Screen()
{
    this->stop();
};

// CHECKED
void Screen::init()
{
    initscr();              /* Start curses mode */
	start_color();			/* Start color mode */
    this->set_resolution();
    raw();                  /* Line buffering disabled */
    curs_set(0);            /* Do not display cursor */
    noecho();               /* Do not echo while we do 'getch()'' */
};

// CHECKED
void Screen::stop()
{
    // TODO: Check exactly what it does
    endwin();
};
