#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>

#include "action_type.hpp"
#include "action.hpp"
#include "element.hpp"
#include "game.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

using namespace std;

int main()
{
    Model::Game * game = new Model::Game("./assets/map.config");
    Model::Keyboard * keyboard = new Model::Keyboard();

    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);


    Controller::Action * action = new Controller::Action(game);

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

    keyboard->init();

    while(true)
    {
        char c;
        if(keyboard->get_key(&c) == true)
        {
            switch(c)
            {
                case 'w':
                case 'W':
                    action->perform(Controller::ActionType::MOVE_UP);
                    break;
                case 'd':
                case 'D':
                    action->perform(Controller::ActionType::MOVE_RIGHT);
                    break;
                case 's':
                case 'S':
                    action->perform(Controller::ActionType::MOVE_DOWN);
                    break;
                case 'a':
                case 'A':
                    action->perform(Controller::ActionType::MOVE_LEFT);
                    break;
            }

            if(c == 'q' || c == 'Q')  break;
        }

        game->render();
    }


    //screen->debug();

    screen->stop();
    keyboard->stop();

    return 0;
}
