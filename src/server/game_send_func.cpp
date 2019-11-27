#include <stdio.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #
#include <thread>

#include "json.hpp"
using json = nlohmann::json;

#include "game_send_func.hpp"

void game_send_func(Model::Game * game)
{
    while(true)
    {
        std::string buffer;
        json j;

        // SERIALIZING GAME'S STATE
        // #####################################################################
        buffer = game->serialize();
        // #####################################################################

        // BROADCASTING GAME'S STATE
        // #####################################################################
        for(int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
        {
            if(game->players[i].empty == false)
            {
                j["alive"] = game->players[i].alive;
                send(game->players[i].fd, j.dump().c_str(), 512, 0);
                //printf("[game_send_thread] I've informed player %d whether he/she is alive or not.\n", i);

                // Player has died
                if(game->players[i].alive == false)
                {
                    game->players[i].empty = true;
                    close(game->players[i].fd);
                    printf("[game_send_thread] Player %d has died.\n", i);
                }
                else
                {
                    send(game->players[i].fd, buffer.c_str(), 512, 0);
                    //printf("[game_send_thread] I've broadcasted game's state to player %d.\n", i);
                }
            }
        }
        // #####################################################################

        // BROADCASTING IS MADE AT EACH 100 MS
        // #####################################################################
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        // #####################################################################
    }
}
