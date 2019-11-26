#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "action_type.hpp"
#include "element.hpp"
#include "element_type.hpp"

namespace Model
{

    class Game
    {
        private:
            struct map
            {
                int l, c;
                ElementType ** state;
            } map;
            struct player
            {
                int x_pos;
                int y_pos;
            } player;
            std::map<ElementType, Element *> elems;
            void load_map(const char * map_path);
            void load_sprites();

        public:
            Game(const char * map_path);
            void update_player(Controller::ActionType type);
            void update_bomb(Controller::ActionType type);
            void render();
            std::string serialize();
            void unserialize(char * buffer);
    };

}

#endif
