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
            // TODO: Think about having references to the threads implementing
            // bomb explosion

        public:
            Action(Model::Game * game);
            ~Action();
            // TODO: Think about implementing init/stop methods to better handle
            // the thread that performs bomb explosion
            int perform(ActionType type, int player_idx);
    };

}

#endif
