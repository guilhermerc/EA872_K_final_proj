#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <string>

namespace Model
{

    class Element
    {
        private:
            int x_pos;  // x and y position from the top right border of its
            int y_pos;  // sprite's matrix representation
            struct sprite
            {
                int l, c;
                char ** matrix;
            } sprite;
            void read_sprite(char * sprite_path);

        public:
            Element(char * sprite_path);
            Element(char * sprite_path, int x_pos, int y_pos);
            ~Element();
            void update(int x_pos, int y_pos);
            void update(char * sprite_path, int x_pos, int y_pos);
            void render();
    };

}
#endif
