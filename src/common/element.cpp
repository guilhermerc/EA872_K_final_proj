#include <fstream>
#include <ncurses.h>
#include <stdlib.h>

#include "element.hpp"

using namespace Model;

void Element::read_sprite(const char * sprite_path)
{
    std::ifstream sprite_file;
    std::string value;

    sprite_file.open(sprite_path);

    // Reading the number of lines and columns of sprite's matrix
    getline(sprite_file, value, ',');
    this->sprite.l = std::stoi(value);
    getline(sprite_file, value, '\n');
    this->sprite.c = std::stoi(value);

    // Allocating heap memory for sprite
    this->sprite.matrix = (char **) malloc(sizeof(char *) * this->sprite.l);
    for(int i = 0; i < this->sprite.l; i++)
        this->sprite.matrix[i] = (char *) malloc(sizeof(char) * this->sprite.c);

    // Reading the sprite's matrix
    for(int i = 0; i < this->sprite.l; i++)
    {
        for(int j = 0; j < this->sprite.c; j++)
        {
            char delim = 0;
            delim = ',';
            // If this char is the last one from its line, the delimiter must be
            // '\n'
            if(j == this->sprite.c - 1)  delim = '\n';
            getline(sprite_file, value, delim);
            this->sprite.matrix[i][j] = (value.c_str())[0];
        }
    }

    sprite_file.close();
}

Element::Element(const char * sprite_path, ElementType et)
{
	this->et = et;

    this->update(0, 0);
    this->read_sprite(sprite_path);
}

Element::~Element()
{
    for(int i = 0; i < this->sprite.c; i++)
        free(this->sprite.matrix[i]);
    free(this->sprite.matrix);
}

void Element::update(int x_pos, int y_pos)
{
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void Element::render(bool is_this_my_player)
{
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

	if(this->et == ElementType::PLAYER_U ||
		this->et == ElementType::PLAYER_R ||
		this->et == ElementType::PLAYER_D ||
		this->et == ElementType::PLAYER_L)
	{
        if(is_this_my_player == true)
            attron(COLOR_PAIR(1));
        else
            attron(COLOR_PAIR(4));
	}
	else if(this->et == ElementType::BOMB ||
			this->et == ElementType::EXPLOSION)
	{
		attron(COLOR_PAIR(2));
	}
	else
	{
		attron(COLOR_PAIR(3));
	}

    for(int i = 0; i < this->sprite.l; i++)
    {
        for(int j = 0; j < this->sprite.c; j++)
        {
            move(this->x_pos + i, this->y_pos + j);
            echochar(this->sprite.matrix[i][j]);
        }
    }

	if(this->et == ElementType::PLAYER_U ||
		this->et == ElementType::PLAYER_R ||
		this->et == ElementType::PLAYER_D ||
		this->et == ElementType::PLAYER_L)
	{
        if(is_this_my_player == true)
            attroff(COLOR_PAIR(1));
        else
            attroff(COLOR_PAIR(4));
	}
	else if(this->et == ElementType::BOMB ||
			this->et == ElementType::EXPLOSION)
	{
		attroff(COLOR_PAIR(2));
	}
	else
	{
		attroff(COLOR_PAIR(3));
	}
}
