#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "action_type.hpp"
#include "element.hpp"
#include "element_type.hpp"

#define MAX_NUMBER_OF_PLAYERS   8

namespace Model
{
    struct map
    {
        int l, c;
        ElementType ** state;
    };

    struct player
    {
        bool empty;
        bool alive;
        int fd;
        int x_pos, y_pos;
    };

    class Game
    {
        private:
            struct map map;
            std::map<ElementType, Element *> elems;
            void load_map(const char * map_path);
            void load_sprites();

        public:
            struct player players[MAX_NUMBER_OF_PLAYERS];
            Game(const char * map_path);
            void init();
            void stop();
            int add_player(int fd);
            void remove_player(int player_idx);
            void update_player(Controller::ActionType type, int player_idx);
            void update_bomb(Controller::ActionType type, int player_idx);
            void render(int player_idx);
            std::string serialize();
            void unserialize(char * buffer);
    };

}

#endif
