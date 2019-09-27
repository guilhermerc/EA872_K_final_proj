#ifndef SCREEN_HPP
#define SCREEN_HPP

namespace View
{

    class Screen
    {
        private:
            int height, width;
            void set_resolution();
            void get_resolution();

            void print_resolution();
            void calibrate();

        public:
            Screen();
            Screen(int heigth, int width);
            ~Screen();
            void init();
            void stop();

            void debug();
    };

}
#endif
