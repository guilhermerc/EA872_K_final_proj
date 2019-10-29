#ifndef ELEMENT_TYPE_HPP
#define ELEMENT_TYPE_HPP

namespace Model
{

    // Types of elements (blocks)
    enum ElementType
    {
                    // Chars used in map.config
        BOMB,
        GROUND,     // G
        PILLAR,     // P
        PLAYER_U,   // U
        PLAYER_R,   // R
        PLAYER_D,   // D
        PLAYER_L,   // L
        EXPLOSION
    };

}

#endif
