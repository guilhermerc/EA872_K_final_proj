// TODO: Discover which one really matters
#include <stdio.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #
#include <thread>

#include "game.hpp"
#include "game_send_func.hpp"

void game_send_func(int socket_fd, Model::Game * game)
{
    while(true)
    {
        std::string buffer_out;

        buffer_out = game->serialize();
        send(socket_fd, buffer_out.c_str(), 512, 0);

        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

    /*
    char c;
    while((*running) == true)
    {
        // If the last character is already processed, then tries to read a new
        // one
        if((*processed) == true)
        {
            c = getch();
            if(c != ERR && c >= 0 && c <= 127)  // 0 - 127 correspond to ASCII
                                                // (not extended) chars
            {
                (*key) = c;
                (*processed) = false;
            }
            else
                (*key) = 0;
        }
        // TODO: Is this rate really necessary?
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
    */
}
