#include <iostream>
#include <ncurses.h>

#include "screen.hpp"

using namespace View;

void Screen::set_resolution()
{
    resizeterm(this->height, this->width);
}

void Screen::get_resolution()
{
    getmaxyx(stdscr, this->height, this->width);
}

void Screen::print_resolution()
{
    std::cout << "H: " << this->height << std::endl;
    std::cout << "W: " << this->width << std::endl;
}

void Screen::calibrate()
{
    // Top left border
    move(0, 0);
    echochar('A');

    // Top right border
    move(0, this->width - 1);
    echochar('B');

    // Bottom left border
    move(this->height - 1, 0);
    echochar('C');

    // Bottom right border
    // For some reason this border is not showed
    move(this->height - 1, this->width - 1);
    echochar('D');
}

Screen::Screen()
{
    // TODO: Set a standard resolution here
    this->height = 0;
    this->width = 0;
};

Screen::Screen(int height, int width)
{
    this->height = height;
    this->width = width;
};

void Screen::init()
{
    initscr();          // Start curses mode
    this->set_resolution();
    raw();              // Line buffering disabled
    curs_set(0);        // Do not display cursor
    noecho();           // Don't echo() while we do getch()
};

void Screen::stop()
{
    // TODO: Check exactly what it does
    endwin();
};

Screen::~Screen()
{
    this->stop();
};

void Screen::debug()
{
    this->print_resolution();
    this->calibrate();
}
