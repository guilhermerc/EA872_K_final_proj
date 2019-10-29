#include <thread>
#include <ncurses.h>

#include "bomb_explosion_func.hpp"

extern bool finish;

// l: number of map lines
// c: number of map columns
// x_pos: bomb x position
// y_pos: bomb y position
void bomb_explosion_func(Model::ElementType ** state, int l, int c, int x_pos, int y_pos)
{
    // Keeps the bomb "alive" during 2000 seconds
    std::this_thread::sleep_for (std::chrono::milliseconds(2000));

    // Explosion

    state[x_pos][y_pos] = Model::ElementType::EXPLOSION;

    if(x_pos - 1 >= 0)
    {
        if(state[x_pos - 1][y_pos] == Model::ElementType::PLAYER_U ||
            state[x_pos - 1][y_pos] == Model::ElementType::PLAYER_R ||
            state[x_pos - 1][y_pos] == Model::ElementType::PLAYER_D ||
            state[x_pos - 1][y_pos] == Model::ElementType::PLAYER_L)
            finish = true;

        if(state[x_pos - 1][y_pos] == Model::ElementType::GROUND)
            state[x_pos - 1][y_pos] = Model::ElementType::EXPLOSION;
    }

    if(x_pos + 1 < l)
    {
        if(state[x_pos + 1][y_pos] == Model::ElementType::PLAYER_U ||
            state[x_pos + 1][y_pos] == Model::ElementType::PLAYER_R ||
            state[x_pos + 1][y_pos] == Model::ElementType::PLAYER_D ||
            state[x_pos + 1][y_pos] == Model::ElementType::PLAYER_L)
            finish = true;

        if(state[x_pos + 1][y_pos] == Model::ElementType::GROUND)
            state[x_pos + 1][y_pos] = Model::ElementType::EXPLOSION;
    }

    if(y_pos - 1 >= 0)
    {
        if(state[x_pos][y_pos - 1] == Model::ElementType::PLAYER_U ||
            state[x_pos][y_pos - 1] == Model::ElementType::PLAYER_R ||
            state[x_pos][y_pos - 1] == Model::ElementType::PLAYER_D ||
            state[x_pos][y_pos - 1] == Model::ElementType::PLAYER_L)
            finish = true;

        if(state[x_pos][y_pos - 1] == Model::ElementType::GROUND)
        {
            state[x_pos][y_pos - 1] = Model::ElementType::EXPLOSION;

            if(y_pos - 2 >= 0)
            {
                if(state[x_pos][y_pos - 2] == Model::ElementType::PLAYER_U ||
                    state[x_pos][y_pos - 2] == Model::ElementType::PLAYER_R ||
                    state[x_pos][y_pos - 2] == Model::ElementType::PLAYER_D ||
                    state[x_pos][y_pos - 2] == Model::ElementType::PLAYER_L)
                    finish = true;

                if(state[x_pos][y_pos - 2] == Model::ElementType::GROUND)
                    state[x_pos][y_pos - 2] = Model::ElementType::EXPLOSION;
            }
        }
    }

    if(y_pos + 1 < c)
    {
        if(state[x_pos][y_pos + 1] == Model::ElementType::PLAYER_U ||
            state[x_pos][y_pos + 1] == Model::ElementType::PLAYER_R ||
            state[x_pos][y_pos + 1] == Model::ElementType::PLAYER_D ||
            state[x_pos][y_pos + 1] == Model::ElementType::PLAYER_L)
            finish = true;

        if(state[x_pos][y_pos + 1] == Model::ElementType::GROUND)
        {

            if(state[x_pos][y_pos + 2] == Model::ElementType::PLAYER_U ||
                state[x_pos][y_pos + 2] == Model::ElementType::PLAYER_R ||
                state[x_pos][y_pos + 2] == Model::ElementType::PLAYER_D ||
                state[x_pos][y_pos + 2] == Model::ElementType::PLAYER_L)
                finish = true;

            state[x_pos][y_pos + 1] = Model::ElementType::EXPLOSION;

            if(y_pos + 2 < c)
            {
                if(state[x_pos][y_pos + 2] == Model::ElementType::GROUND)
                    state[x_pos][y_pos + 2] = Model::ElementType::EXPLOSION;
            }
        }
    }

    // Keeps the explosion during 1 second
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));

    // Returns map's original state (before explosion)

    state[x_pos][y_pos] = Model::ElementType::GROUND;

    if(x_pos - 1 >= 0)
    {
        if(state[x_pos - 1][y_pos] == Model::ElementType::EXPLOSION)
            state[x_pos - 1][y_pos] = Model::ElementType::GROUND;
    }

    if(x_pos + 1 < l)
    {
        if(state[x_pos + 1][y_pos] == Model::ElementType::EXPLOSION)
            state[x_pos + 1][y_pos] = Model::ElementType::GROUND;
    }

    if(y_pos - 1 >= 0)
    {
        if(state[x_pos][y_pos - 1] == Model::ElementType::EXPLOSION)
        {
            state[x_pos][y_pos - 1] = Model::ElementType::GROUND;
            if(y_pos - 2 >= 0)
            {
                if(state[x_pos][y_pos - 2] == Model::ElementType::EXPLOSION)
                    state[x_pos][y_pos - 2] = Model::ElementType::GROUND;
            }
        }
    }

    if(y_pos + 1 < c)
    {
        if(state[x_pos][y_pos + 1] == Model::ElementType::EXPLOSION)
        {
            state[x_pos][y_pos + 1] = Model::ElementType::GROUND;
            if(y_pos + 2 < c)
            {
                if(state[x_pos][y_pos + 2] == Model::ElementType::EXPLOSION)
                    state[x_pos][y_pos + 2] = Model::ElementType::GROUND;
            }
        }
    }

    return;
}
