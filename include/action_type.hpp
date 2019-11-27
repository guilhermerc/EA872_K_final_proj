#ifndef ACTION_TYPE_HPP
#define ACTION_TYPE_HPP

namespace Controller
{

    // Types of action coming from user
    enum ActionType
    {
        MOVE_UP,
        MOVE_RIGHT,
        MOVE_DOWN,
        MOVE_LEFT,
        SPAWN_BOMB,
        ADD_PLAYER,
        REMOVE_PLAYER
    };

}

#endif
