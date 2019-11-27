#include <stdio.h>
#include <string.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

#include "json.hpp"
using json = nlohmann::json;

#include "game_recv_func.hpp"

extern bool alive;

void game_recv_func(int socket_fd, Model::Game * game, int player_idx)
{
    while(alive)
    {
        char input_buffer[512];
        json j;

        // AM I STILL ALIVE?
        // #####################################################################
        recv(socket_fd, input_buffer, 512, 0);
        std::string aux(input_buffer);
        j = json::parse(aux);
        j["alive"].get_to(alive);
        // #####################################################################

        if(!alive)  break;

        // WAITING FOR GAME'S STATE
        // #####################################################################
        // printf("[game_recv_thread] Waiting for game's state update!\n");
        if(recv(socket_fd, input_buffer, 512, 0) <= 0)  break;
        // printf("[game_recv_thread] Game's state received: %s\n", input_buffer);
        // #####################################################################

        // UNSERIALIZING GAME'S STATE
        // #####################################################################
        game->unserialize(input_buffer);
        // printf("[game_recv_thread] Game's state unserialized!\n");
        // #####################################################################

        // RENDERING GAME'S STATE
        // #####################################################################
        game->render(player_idx);
        // printf("[game_recv_thread] Game's state rendered!\n");
        // #####################################################################
    }
}
