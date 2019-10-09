#include <thread>
#include <vector>

#include "action_type.hpp"
#include "action.hpp"
#include "element.hpp"
#include "game.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

using namespace std;

bool finish = false;

int main()
{
    // Model objects
    // Although these objects have some View/Controller methods, they are
    // intended to be used as interfaces to objects related to these components
    Model::Game * game = new Model::Game("./assets/map.config");
    Model::Keyboard * keyboard = new Model::Keyboard();

    // View objects
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);

    // Controller objects
    Controller::Action * action = new Controller::Action(game);

    // TODO: REMOVE HARDCODED VALUES
    // TODO: Encapsulate this inside Game class
    // TODO: Renderize efficiently (only load the border sprite once)
    // Allocating borders
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
    {
        borders.push_back(new Model::Element("./assets/sprites/border.sprite"));
        (borders.back())->update(3 + 5 * (i / 13), 25 + 7 * (i % 13));
    }


    // Intializing objects
    // game->init();
    // action->init();
    screen->init();
    keyboard->init();

    // TODO: Call this from Screen object
    for(int i = 0; i < 91; i++)
        borders[i]->render();

    while(!finish)
    {
        char c;
        // If there's a new key to be processed ('true')
        if(keyboard->get_key(&c) == true)
        {
            switch(c)
            {
                case 'w':
                case 'W':
                    // Player moves upwards, if possible
                    action->perform(Controller::ActionType::MOVE_UP);
                    break;
                case 'd':
                case 'D':
                    // Player moves rightwards, if possible
                    action->perform(Controller::ActionType::MOVE_RIGHT);
                    break;
                case 's':
                case 'S':
                    // Player moves downwards, if possible
                    action->perform(Controller::ActionType::MOVE_DOWN);
                    break;
                case 'a':
                case 'A':
                    // Player move leftwards, if possible
                    action->perform(Controller::ActionType::MOVE_LEFT);
                    break;
                case 'j':
                case 'J':
                    // Player spawns bomb in its orientation, if possible
                    action->perform(Controller::ActionType::SPAWN_BOMB);
                    break;
            }

            // Quits the game
            if(c == 'q' || c == 'Q')  break;
        }

        // Refreshing the screen at most 200 times per second
        std::this_thread::sleep_for (std::chrono::milliseconds(5));
        // TODO: Call this from Screen object
        game->render();
    }

    keyboard->stop();
    screen->stop();
    // action->stop();
    // game->stop();

    return 0;
}
