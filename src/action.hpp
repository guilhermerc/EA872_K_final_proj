#ifndef ACTION_HPP
#define ACTION_HPP

#include "action_type.hpp"
#include "game.hpp"

namespace Controller
{

    class Action
    {
        private:
            Model::Game * game;

        public:
            Action(Model::Game * game);
            ~Action();
            void perform(ActionType type);
    };

}

#endif
