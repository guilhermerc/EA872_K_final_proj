#include <fstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>

#include <ncurses.h>


#include "json.hpp"
using json = nlohmann::json;

#include "bomb_explosion_func.hpp"
#include "game.hpp"

using namespace Model;

void Game::load_map(const char * map_path)
{
    std::ifstream map_file;
    std::string value;

    map_file.open(map_path);

    // Reading the number of lines and columns of map
    getline(map_file, value, ',');
    this->map.l = std::stoi(value);
    getline(map_file, value, '\n');
    this->map.c = std::stoi(value);

    // Allocating heap memory for map's state matrix
    this->map.state = (ElementType **) malloc(sizeof(ElementType *) * this->map.l);
    for(int i = 0; i < this->map.l; i++)
        this->map.state[i] = (ElementType *) malloc(sizeof(ElementType) * this->map.c);

    // Reading the map's initial state
    for(int i = 0; i < this->map.l; i++)
    {
        for(int j = 0; j < this->map.c; j++)
        {
            char delim = 0;
            delim = ',';
            // If this char is the last one from its line, the delimiter must be
            // '\n'
            if(j == this->map.c - 1)  delim = '\n';
            getline(map_file, value, delim);

            ElementType type;
            switch((value.c_str())[0])
            {
                case 'G':
                    type = GROUND;
                    break;
                case 'P':
                    type = PILLAR;
                    break;
                case 'U':
                    this->player.x_pos = i;
                    this->player.y_pos = j;
                    type = PLAYER_U;
                    break;
            }

            this->map.state[i][j] = type;
        }
    }

    map_file.close();
}

void Game::load_sprites()
{
    this->elems.insert({BOMB, new Model::Element("../assets/sprites/bomb.sprite", Model::ElementType::BOMB)});
    this->elems.insert({PILLAR, new Model::Element("../assets/sprites/pillar.sprite", Model::ElementType::PILLAR)});
    this->elems.insert({GROUND, new Model::Element("../assets/sprites/ground.sprite", Model::ElementType::GROUND)});
    this->elems.insert({PLAYER_U, new Model::Element("../assets/sprites/player_u.sprite", Model::ElementType::PLAYER_U)});
    this->elems.insert({PLAYER_R, new Model::Element("../assets/sprites/player_r.sprite", Model::ElementType::PLAYER_R)});
    this->elems.insert({PLAYER_D, new Model::Element("../assets/sprites/player_d.sprite", Model::ElementType::PLAYER_D)});
    this->elems.insert({PLAYER_L, new Model::Element("../assets/sprites/player_l.sprite", Model::ElementType::PLAYER_L)});
    this->elems.insert({EXPLOSION, new Model::Element("../assets/sprites/explosion.sprite", Model::ElementType::EXPLOSION)});
}

Game::Game(const char * map_path)
{
    this->load_map(map_path);
    this->load_sprites();
}

// Controller
void Game::update_player(Controller::ActionType type)
{
    switch(type)
    {
        case Controller::ActionType::MOVE_UP:
            // Checks if player is NOT already correctly oriented
            if(this->map.state[this->player.x_pos][this->player.y_pos] != PLAYER_U)
                this->map.state[this->player.x_pos][this->player.y_pos] = PLAYER_U;
            // If the player movement is allowed
            else if(this->player.x_pos - 1 >= 0)
            {
                // Then check if player is trying to move between allowed blocks
                if(this->map.state[this->player.x_pos - 1][this->player.y_pos] == GROUND)
                {
                    this->map.state[this->player.x_pos][this->player.y_pos] = GROUND;
                    this->map.state[--this->player.x_pos][this->player.y_pos] = PLAYER_U;
                }
            }
            break;
        case Controller::ActionType::MOVE_RIGHT:
            // Checks if player is NOT already correctly oriented
            if(this->map.state[this->player.x_pos][this->player.y_pos] != PLAYER_R)
                this->map.state[this->player.x_pos][this->player.y_pos] = PLAYER_R;
            // If the player movement is allowed
            else if(this->player.y_pos + 1 < this->map.c)
            {
                // Then check if player is trying to move between allowed blocks
                if(this->map.state[this->player.x_pos][this->player.y_pos + 1] == GROUND)
                {
                    this->map.state[this->player.x_pos][this->player.y_pos] = GROUND;
                    this->map.state[this->player.x_pos][++this->player.y_pos] = PLAYER_R;
                }
            }
            break;
        case Controller::ActionType::MOVE_DOWN:
            // Checks if player is NOT already correctly oriented
            if(this->map.state[this->player.x_pos][this->player.y_pos] != PLAYER_D)
                this->map.state[this->player.x_pos][this->player.y_pos] = PLAYER_D;
            // If the player movement is allowed
            else if(this->player.x_pos + 1 < this->map.l)
            {
                // Then check if player is trying to move between allowed blocks
                if(this->map.state[this->player.x_pos + 1][this->player.y_pos] == GROUND)
                {
                    this->map.state[this->player.x_pos][this->player.y_pos] = GROUND;
                    this->map.state[++this->player.x_pos][this->player.y_pos] = PLAYER_D;
                }
            }
            break;
        case Controller::ActionType::MOVE_LEFT:
            // Checks if player is NOT already correctly oriented
            if(this->map.state[this->player.x_pos][this->player.y_pos] != PLAYER_L)
                this->map.state[this->player.x_pos][this->player.y_pos] = PLAYER_L;
            // If the player movement is allowed
            else if(this->player.y_pos - 1 >= 0)
            {
                // Then check if player is trying to move between allowed blocks
                if(this->map.state[this->player.x_pos][this->player.y_pos - 1] == GROUND)
                {
                    this->map.state[this->player.x_pos][this->player.y_pos] = GROUND;
                    this->map.state[this->player.x_pos][--this->player.y_pos] = PLAYER_L;
                }
            }
            break;
    }
}

// Controller
void Game::update_bomb(Controller::ActionType type)
{
    bool spawned = false;
    int x_pos = 0, y_pos = 0;
    switch(type)
    {
        case Controller::ActionType::SPAWN_BOMB:
            switch(this->map.state[this->player.x_pos][this->player.y_pos])
            {
                case PLAYER_U:
                    if(this->player.x_pos - 1 >= 0)
                    {
                        if(this->map.state[this->player.x_pos - 1][this->player.y_pos] == GROUND)
                        {
                            this->map.state[this->player.x_pos - 1][this->player.y_pos] = BOMB;
                            spawned = true;
                            x_pos = this->player.x_pos - 1;
                            y_pos = this->player.y_pos;
                        }
                    }
                    break;
                case PLAYER_R:
                    if(this->player.y_pos + 1 < this->map.c)
                    {
                        if(this->map.state[this->player.x_pos][this->player.y_pos + 1] == GROUND)
                        {
                            this->map.state[this->player.x_pos][this->player.y_pos + 1] = BOMB;
                            spawned = true;
                            x_pos = this->player.x_pos;
                            y_pos = this->player.y_pos + 1;
                        }
                    }
                    break;
                case PLAYER_D:
                    if(this->player.x_pos + 1 < this->map.l)
                    {
                        if(this->map.state[this->player.x_pos + 1][this->player.y_pos] == GROUND)
                        {
                            this->map.state[this->player.x_pos + 1][this->player.y_pos] = BOMB;
                            spawned = true;
                            x_pos = this->player.x_pos + 1;
                            y_pos = this->player.y_pos;
                        }
                    }
                    break;
                case PLAYER_L:
                    if(this->player.y_pos - 1 >= 0)
                    {
                        if(this->map.state[this->player.x_pos][this->player.y_pos - 1] == GROUND)
                        {
                            this->map.state[this->player.x_pos][this->player.y_pos - 1] = BOMB;
                            spawned = true;
                            x_pos = this->player.x_pos;
                            y_pos = this->player.y_pos - 1;
                        }
                    }
                    break;
            }
    }

    // If a bomb was spawned
    if(spawned == true)
    {
        // Creates a thread to deal with its explosion procedure
        std::thread new_thread(bomb_explosion_func, this->map.state, this->map.l, this->map.c, x_pos, y_pos);
        new_thread.detach();
    }
}

// View
void Game::render()
{
    for(int i = 0; i < this->map.l; i++)
    {
        for(int j = 0; j < this->map.c; j++)
        {
            // TODO: REMOVE HARDCODED VALUES
            this->elems[this->map.state[i][j]]->update(4 + 5 * i, 26 + 7 * j);
            this->elems[this->map.state[i][j]]->render();
        }
    }
};

std::string Game::serialize()
{
    json j, state;

    j["l"] = this->map.l;
    j["c"] = this->map.c;

    for(int i = 0; i < this->map.l; i++)
    {
        for(int j = 0; j < this->map.c; j++)
        {
            state.push_back((int)this->map.state[i][j]);

            /* ########## REMOVE ##########
            // TODO: REMOVE HARDCODED VALUES
            this->elems[this->map.state[i][j]]->update(4 + 5 * i, 26 + 7 * j);
            this->elems[this->map.state[i][j]]->render();
            */ // ########## REMOVE ##########
        }
    }

    j["state"] = state;

    return j.dump();
}

void Game::unserialize(char * buffer)
{
    std::string buffer_aux(buffer);

    json j, state;
    j = json::parse(buffer_aux);

    j["l"].get_to(this->map.l);
    j["c"].get_to(this->map.c);
    state = j["state"];

    for(int i = 0, aux = 0; i < this->map.l; i++)
    {
        for(int j = 0; j < this->map.c; j++)
        {
            this->map.state[i][j] = state.at(aux);
            aux++;

            /* ########## REMOVE ##########
            // TODO: REMOVE HARDCODED VALUES
            this->elems[this->map.state[i][j]]->update(4 + 5 * i, 26 + 7 * j);
            this->elems[this->map.state[i][j]]->render();
            */ // ########## REMOVE ##########
        }
    }

}
