#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <string>
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
            bool is_there_a_new_key();
            std::string serialize();
            void unserialize(char * buffer);

            // ########## DEBUG PURPOSES ONLY ##########
            char get_key();
            // ########## DEBUG PURPOSES ONLY ##########
    };

}

#endif
