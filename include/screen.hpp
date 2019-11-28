#ifndef SCREEN_HPP
#define SCREEN_HPP

namespace View
{
    
    // CHECKED
    class Screen
    {
        private:
            int height, width;
            void set_resolution();

        public:
            Screen(int heigth, int width);
            ~Screen();
            void init();
            void stop();
            // TODO: Create a render method that wrappers Game's render method
    };

}
#endif
