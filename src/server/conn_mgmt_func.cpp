#include <thread>

#include <stdio.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

#include "json.hpp"
using json = nlohmann::json;

#include "conn_mgmt_func.hpp"
#include "kboard_recv_func.hpp"

void conn_mgmt_func(int socket_fd, Model::Keyboard * keyboard, Controller::Action * action)
{
    while(true)
    {
        struct sockaddr_in client;
        socklen_t client_size = (socklen_t) sizeof(client);
        int player_idx, connection_fd;
        json j;

        // WAITING FOR CONNECTIONS
        // #####################################################################
        printf("[conn_mgmt_thread] Waiting for a connection request...\n");
        connection_fd = accept(socket_fd, (struct sockaddr*) &client, &client_size);
        printf("[conn_mgmt_thread] A client has connected with me!\n");
        // #####################################################################


        // TRYING TO ADD THE NEW CLIENT TO THE GAME
        // #####################################################################
        player_idx = action->perform(Controller::ActionType::ADD_PLAYER, connection_fd);
        // #####################################################################


        if(player_idx == -1)
        {
            // SERVER IS FULL, CLIENT HAS NOT JOINED THE GAME
            // #################################################################
            printf("[conn_mgmt_thread] Server is currently full! Closing connection with client.\n");
            j["idx"] = -1;  send(connection_fd, j.dump().c_str(), 128, 0);
            close(connection_fd);
            // #################################################################
        }
        else
        {
            // CREATING A THREAD TO PROCESS INCOMING DATA FROM CLIENT
            // #################################################################
            printf("[conn_mgmt_thread] Player %d has joined the game!\n", player_idx);
            j["idx"] = player_idx;  send(connection_fd, j.dump().c_str(), 128, 0);
            std::thread kboard_recv_thread(kboard_recv_func, connection_fd, player_idx, keyboard, action);
            kboard_recv_thread.detach();
            // #################################################################
        }
    }
}
