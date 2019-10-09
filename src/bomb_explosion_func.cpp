#include <thread>
#include <ncurses.h>

#include "bomb_explosion_func.hpp"

void bomb_explosion_func(Model::ElementType ** state, int x_pos, int y_pos)
{
    std::this_thread::sleep_for (std::chrono::milliseconds(5000));
    state[x_pos][y_pos] = Model::ElementType::GROUND;

    return;
}
