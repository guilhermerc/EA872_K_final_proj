#include <stdio.h>
#include <string.h>

/* Socket-related headers */
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

#include "json.hpp"
using json = nlohmann::json;

#include "game_recv_func.hpp"

#define BUFFER_IN_MAX_SIZE  512

extern bool alive;

void game_recv_func(int socket_fd, Model::Game * game, int player_idx)
{
    while(alive)
    {
        char buffer_in[BUFFER_IN_MAX_SIZE];
        json j;

        // AM I STILL ALIVE?
        // #####################################################################
        recv(socket_fd, buffer_in, BUFFER_IN_MAX_SIZE, 0);
        // #####################################################################

        // PARSING RECEIVED DATA
        // #####################################################################
        std::string aux(buffer_in);

        j = json::parse(aux);
        j["alive"].get_to(alive);
        // #####################################################################

        // CHECKING IF I'M ALIVE
        // #####################################################################
        /* If I'm dead, breaks while loop and finishes this thread */
        if(!alive)
        {
            //printf("[game_recv_thread] You have died :(\n");
            break;
        }
        // #####################################################################

        // WAITING FOR GAME'S STATE
        // #####################################################################
        //printf("[game_recv_thread] Waiting for game's state update!\n");
        /* If an error has ocurred or server has performed an orderly shutdown,
        "kills" client and finishes this thread */
        if(recv(socket_fd, buffer_in, BUFFER_IN_MAX_SIZE, 0) <= 0)
        {
            /*
            printf("[game_recv_thread] Server has closed our communication "
                    "or a pipe-related error has ocurred!\n");
            */
            alive = false;
            break;
        }
        //printf("[game_recv_thread] Game's state received: %s\n", buffer_in);
        // #####################################################################

        // UNSERIALIZING GAME'S STATE
        // #####################################################################
        game->unserialize(buffer_in);
        //printf("[game_recv_thread] Game's state unserialized!\n");
        // #####################################################################

        // RENDERING GAME'S STATE
        // #####################################################################
        game->render(player_idx);
        //printf("[game_recv_thread] Game rendered!\n");
        // #####################################################################
    }
}
