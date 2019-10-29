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
void Action::perform(ActionType type)
{
    switch(type)
    {
        case MOVE_UP:
        case MOVE_RIGHT:
        case MOVE_DOWN:
        case MOVE_LEFT:
            this->game->update_player(type);
            break;
        case SPAWN_BOMB:
            this->game->update_bomb(type);
            break;
    }
}
