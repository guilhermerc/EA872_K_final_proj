#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>

#include "element.hpp"
#include "game.hpp"
#include "screen.hpp"

using namespace std;

int main()
{
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);
    Model::Game * game = new Model::Game("./assets/map.config");

    // TODO: Get map dimensions from Map object
    // TODO: Get border dimensions from its Element object
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
        borders.push_back(new Model::Element("./assets/sprites/border.sprite", 3 + 5 * (i / 13), 25 + 7 * (i % 13)));

    // I saw something about using these global variables, but they just don't
    // work
    // cout << "LINES: " << LINES << endl;
    // cout << "COLS:  " << COLS << endl;

    screen->init();

    for(int i = 0; i < 91; i++)
        borders[i]->render();

    game->render();

    //screen->debug();
    std::this_thread::sleep_for(std::chrono::milliseconds(120000));
    screen->stop();

    return 0;
}
