#include <stdio.h>
#include <ncurses.h>
#include <signal.h>
#include <thread>
#include <vector>

/* Socket-related headers */
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

#include "game.hpp"
#include "game_recv_func.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

#include "json.hpp"
using json = nlohmann::json;

#define BUFFER_IN_MAX_SIZE  128
#define BUFFER_OUT_MAX_SIZE 128

using namespace std;

/* Global variable to indicate whether this player is alive or not */
bool alive = true;

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        // INFORMING USAGE
        // #####################################################################
        printf("Usage: ./main <SERVER_IP>\n");
        return 0;
        // #####################################################################
    }

    // IGNORING SIGPIPE
    // #########################################################################
    /* Changing the default behavior (terminate) of this process when it tries
    to write to a pipe without readers. */
    signal(SIGPIPE, SIG_IGN);
    // #########################################################################

    // INSTANTIATING MODEL OBJECTS
    // #########################################################################
    /* Although these objects have some View/Controller methods, they are
    intended to be used only as interfaces to objects related to these
    components */
    Model::Game * game = new Model::Game("../assets/map.config");
    Model::Keyboard * keyboard = new Model::Keyboard();
    // #########################################################################

    // INSTANTIATING VIEW OBJECT
    // #########################################################################
    /* Maximum height defined as 44 */
    /* Maximum width defined as 143 */
    View::Screen * screen = new View::Screen(44, 143);
    // #########################################################################

    // ALLOCATING BORDERS
    // #########################################################################
    /* TODO: Remove hardcoded values */
    /* TODO: Encapsulate this inside Game class */
    /* TODO: Renderize borders efficiently (load border's sprite only once) */
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
    {
        borders.push_back(new Model::Element("../assets/sprites/border.sprite",\
                            Model::ElementType::GROUND));
        (borders.back())->update(3 + 5 * (i / 13), 25 + 7 * (i % 13));
    }
    // #########################################################################

    // INITIALIZING OBJECTS
    // #########################################################################
    game->init();
    keyboard->init();
    screen->init();
    // #########################################################################

    // RENDERING BORDERS
    // #########################################################################
    /* TODO: Remove hardcoded values */
    /* TODO: Call this from Screen object */
    for(int i = 0; i < 91; i++)
        borders[i]->render(false);
    // #########################################################################

    // TRYING TO CONNECT TO SERVER
    // #########################################################################
    int socket_fd;
    struct sockaddr_in target;
    char buffer_in[BUFFER_IN_MAX_SIZE];

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    //printf("[main thread] Socket created!\n");

    target.sin_family = AF_INET;
    target.sin_port = htons(3001);
    /* Using the IP address provided as argument */
    inet_aton(argv[1], &(target.sin_addr));

    //printf("[main thread] Attempting to connect to server...\n");
    while(connect(socket_fd, (struct sockaddr*) &target, sizeof(target)) != 0)
    {
        //printf("[main thread] Connection problem. Trying again in 1 sec...\n");
        sleep(1);
    }
    //printf("[main thread] Connection to server stablished!\n");
    // #########################################################################

    // WAITING FOR SERVER RESPONSE
    // #########################################################################
    recv(socket_fd, buffer_in, BUFFER_IN_MAX_SIZE, 0);
    // #########################################################################

    // PARSING SERVER RESPONSE
    // #########################################################################
    json j;
    string buffer_aux(buffer_in);
    int player_idx = 0;

    j = json::parse(buffer_aux);
    j["idx"].get_to(player_idx);
    // #########################################################################

    // INTERPRETING SERVER RESPONSE
    // #########################################################################
    if(player_idx == -1)
    {
        //printf("[main thread] Server is currently full! Closing client. \n");
        return 0;
    }
    else
    {
        /*
        printf("[main thread] You have successfully joined the server! Your "
                "index is %d!\n", player_idx);
        */
    }
    // #########################################################################

    // CREATING A THREAD TO HANDLE DATA RECEIVED FROM SERVER
    // #########################################################################
    //printf("[main thread] Creating game_recv_thread.\n");
    std::thread game_recv_thread(game_recv_func, socket_fd, game, player_idx);
    // #########################################################################


    // MAIN THREAD WILL BE RESPONSIBLE FOR SENDING KEYBOARD DATA TO SERVER
    // #########################################################################
    while(alive)
    {
        string buffer_out;
        if(keyboard->is_there_a_new_key() == true)
        {
            //printf("[main_thread] I've got a new key!\n");
            buffer_out = keyboard->serialize();
            //printf("[main_thread] Serialized key: %s\n", buffer_out.c_str());

            send(socket_fd, buffer_out.c_str(), BUFFER_OUT_MAX_SIZE, 0);
        }
    }
    // #########################################################################

    // WAITING GAME_RECV_THREAD TO JOIN
    // #########################################################################
    game_recv_thread.join();
    // #########################################################################

    // STOPING OBJECTS
    // #########################################################################
    screen->stop();
    printf("[main_thread] You have died (or a connection error has ocurred). "
            "Please, press ENTER to leave the program.\n");
    keyboard->stop();
    game->stop();
    // #########################################################################

    // CLOSING SOCKET
    // #########################################################################
    close(socket_fd);
    // #########################################################################

    return 0;
}
