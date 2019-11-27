#include <signal.h>
#include <thread>

#include "action.hpp"
#include "conn_mgmt_func.hpp"
#include "game.hpp"
#include "game_send_func.hpp"
#include "keyboard.hpp"

#include <stdio.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

using namespace std;

bool finish = false;

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Usage: ./main <SERVER_IP>\n");
        return 0;
    }

    signal(SIGPIPE, SIG_IGN);

    // INSTANTIATING MODEL OBJECTS
    // #########################################################################
    /* Although these objects have some View/Controller methods, they are
    intended to be used as interfaces to objects related to these components */
    Model::Game * game = new Model::Game("../assets/map.config");
    Model::Keyboard * keyboard = new Model::Keyboard();
    // #########################################################################


    // INSTANTIATING CONTROLLER OBJECT
    // #########################################################################
    Controller::Action * action = new Controller::Action(game);
    // #########################################################################


    // CREATING A PASSIVE SOCKET
    // #########################################################################
    int socket_fd;
    struct sockaddr_in myself;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("[main_thread] Socket created!\n");

    myself.sin_family = AF_INET;
    myself.sin_port = htons(3001);
    inet_aton(argv[1], &(myself.sin_addr));

    printf("[main_thread] Attempting to open port 3001...\n");

    while(bind(socket_fd, (struct sockaddr*)&myself, sizeof(myself)) != 0)
    {
        printf("[main_thread] Problems while attempting to open port 3001. Trying again in 1 sec...\n");
        sleep(1);
    }
    printf("[main_thread] Port 3001 opened!\n");

    listen(socket_fd, MAX_NUMBER_OF_PLAYERS);
    printf("[main_thread] Listening on port 3001...\n");
    // #########################################################################


    // CREATING A THREAD THAT WILL MANAGE INCOMING CONNECTIONS
    // #########################################################################
    printf("[main_thread] Creating conn_mgmt_thread.\n");
    std::thread conn_mgmt_thread(conn_mgmt_func, socket_fd, keyboard, action);
    // #########################################################################


    // CREATING A THREAD THAT WILL BROADCAST GAME'S STATE
    // #########################################################################
    printf("[main_thread] Creating game_send_thread.\n");
    std::thread game_send_thread(game_send_func, game);
    // #########################################################################


    // WAITING FOR THREADS TO END
    // #########################################################################
    conn_mgmt_thread.join();
    game_send_thread.join();
    // #########################################################################

    close(socket_fd);
    return 0;
}
