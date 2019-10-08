#ifndef GAME_HPP
#define GAME_HPP

#include <map>

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
            std::map<ElementType, Element *> elems;
            void load_map(char * map_path);
            void load_sprites();

        public:
            Game(char * map_path);
            void render();
    };

}

#endif
