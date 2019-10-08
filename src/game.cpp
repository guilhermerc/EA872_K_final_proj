#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "game.hpp"

using namespace Model;

Game::Game(char * map_path)
{
    this->load_map(map_path);
    this->load_sprites();
}

void Game::load_map(char * map_path)
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
            // TODO: REMOVE HARDCODED VALUES
            switch((value.c_str())[0])
            {
                case 'B':
                    type = BORDER;
                    break;
                case 'G':
                    type = GROUND;
                    break;
                case 'P':
                    type = PILLAR;
                    break;
                case 'D':
                    this->player.x_pos = i;
                    this->player.y_pos = j;
                    type = PLAYER_D;
                    break;
                case 'L':
                    this->player.x_pos = i;
                    this->player.y_pos = j;
                    type = PLAYER_L;
                    break;
                case 'R':
                    this->player.x_pos = i;
                    this->player.y_pos = j;
                    type = PLAYER_R;
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
    this->elems.insert({BORDER, new Model::Element("./assets/sprites/border.sprite")});
    this->elems.insert({PILLAR, new Model::Element("./assets/sprites/pillar.sprite")});
    this->elems.insert({GROUND, new Model::Element("./assets/sprites/ground.sprite")});
    this->elems.insert({PLAYER_U, new Model::Element("./assets/sprites/player_u.sprite")});
    this->elems.insert({PLAYER_R, new Model::Element("./assets/sprites/player_r.sprite")});
    this->elems.insert({PLAYER_D, new Model::Element("./assets/sprites/player_d.sprite")});
    this->elems.insert({PLAYER_L, new Model::Element("./assets/sprites/player_l.sprite")});
}

void Game::render()
{
    for(int i = 0; i < this->map.l; i++)
    {
        for(int j = 0; j < this->map.c; j++)
        {
            // TODO: Make render method receive the coordinates arguments
            // TODO: REMOVE HARDCODED VALUES
            this->elems[this->map.state[i][j]]->update(4 + 5 * i, 26 + 7 * j);
            this->elems[this->map.state[i][j]]->render();
        }
    }
};

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
