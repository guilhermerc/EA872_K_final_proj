#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>

#include "element.hpp"
#include "screen.hpp"

using namespace std;

int main()
{
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);

    /*
    Model::Element * player_u = new Model::Element("./sprites/player_u.sprite", 1, 0);
    Model::Element * player_r = new Model::Element("./sprites/player_r.sprite", 1, 10);
    Model::Element * player_d = new Model::Element("./sprites/player_d.sprite", 1, 20);
    Model::Element * player_l = new Model::Element("./sprites/player_l.sprite", 1, 30);
    Model::Element * ground = new Model::Element("./sprites/ground.sprite", 1, 40);
    Model::Element * pillar = new Model::Element("./sprites/pillar.sprite", 1, 50);
    Model::Element * border = new Model::Element("./sprites/border.sprite", 0, 60);
    */

    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
        borders.push_back(new Model::Element("./sprites/border.sprite", 5 * (i / 13), 7 * (i % 13)));

    // I saw something about using these global variables, but they just don't
    // work
    // cout << "LINES: " << LINES << endl;
    // cout << "COLS:  " << COLS << endl;

    screen->init();

    for(int i = 0; i < 91; i++)
        borders[i]->render();

    //screen->debug();
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    screen->stop();

    return 0;
}
