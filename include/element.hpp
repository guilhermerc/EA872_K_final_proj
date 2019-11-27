#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "element_type.hpp"

namespace Model
{

    class Element
    {
        private:
            // TODO: Remove these attributes afters merging update and render
            // methods
            int x_pos;  // x and y position from the top right border of its
            int y_pos;  // sprite's matrix representation
            struct sprite
            {
                int l, c;
                char ** matrix;
            } sprite;

		ElementType et;

            void read_sprite(const char * sprite_path);

        public:
            Element(const char * sprite_path, ElementType et);
            ~Element();
            // TODO: update and render should merge, as there's no need to hold
            // x_pos and y_pos
            void update(int x_pos, int y_pos);
            void render(bool is_this_my_player);
    };

}

#endif
