#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <thread>

namespace Model
{

    class Keyboard
    {
        private:
            char key;
            bool processed;
            bool running;
            std::thread kboard_thread;

        public:
            Keyboard();
            ~Keyboard();
            void init();
            void stop();
            bool get_key(char * c);
    };

}

#endif
