#include "action.hpp"

using namespace Controller;

Action::Action(Model::Game * game)
{
    this->game = game;
}

Action::~Action()
{
    // this->stop()
    // It might have this->thread.join()
}

// Acts like a wrapper/proxy
int Action::perform(ActionType type, int value)
{
    int index;
    switch(type)
    {
        case MOVE_UP:
        case MOVE_RIGHT:
        case MOVE_DOWN:
        case MOVE_LEFT:
            this->game->update_player(type, value);
            break;
        case SPAWN_BOMB:
            this->game->update_bomb(type, value);
            break;
        case ADD_PLAYER:
            index = this->game->add_player(value);
            break;
        case REMOVE_PLAYER:
            this->game->remove_player(value);
            break;
    }

    return index;
}
