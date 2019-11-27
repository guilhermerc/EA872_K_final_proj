#include <ncurses.h>
#include <signal.h>
#include <thread>
#include <vector>

#include "game.hpp"
#include "game_recv_func.hpp"
#include "keyboard.hpp"
#include "screen.hpp"

#include "json.hpp"
using json = nlohmann::json;

#include <stdio.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

using namespace std;

bool alive = true;

int main()
{
    signal(SIGPIPE, SIG_IGN);

    // INSTANTIATING MODEL OBJECTS
    // ###################################################################
    // Although these objects have some View/Controller methods, they are
    // intended to be used as interfaces to objects related to these components
    Model::Game * game = new Model::Game("../assets/map.config");
    Model::Keyboard * keyboard = new Model::Keyboard();
    // ###################################################################


    // INSTANTIATING VIEW OBJECT
    // ###################################################################
    // View objects
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);
    // ###################################################################


    // ALLOCATING BORDERS
    // ###################################################################
    // TODO: REMOVE HARDCODED VALUES
    // TODO: Encapsulate this inside Game class
    // TODO: Renderize efficiently (only load the border sprite once)
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
    {
        borders.push_back(new Model::Element("../assets/sprites/border.sprite", Model::ElementType::GROUND));
        (borders.back())->update(3 + 5 * (i / 13), 25 + 7 * (i % 13));
    }
    // ###################################################################


    // INITIALIZING OBJECTS
    // ###################################################################
    screen->init();
    keyboard->init();
    // ###################################################################


    // RENDERING BORDERS
    // ###################################################################
    // TODO: Call this from Screen object
    for(int i = 0; i < 91; i++)
        borders[i]->render(false);
    // ###################################################################


    // TRYING TO CONNECT TO SERVER
    // ###################################################################
    int socket_fd;
    struct sockaddr_in target;
    char input_buffer[128];
    json j; int player_idx = 0;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // printf("[main thread] Socket created!\n");

    target.sin_family = AF_INET;
    target.sin_port = htons(3001);
    inet_aton("127.0.0.1", &(target.sin_addr));

    // printf("[main thread] Attempting to connect to server...\n");
    while(connect(socket_fd, (struct sockaddr*) &target, sizeof(target)) != 0)
    {
        // printf("[main thread] Connection problem. Trying again in 1 sec...\n");
        sleep(1);
    }
    // printf("[main thread] Connection to server stablished!\n");
    // ###################################################################


    // WAITING FOR SERVER RESPONSE
    // ###################################################################
    recv(socket_fd, input_buffer, 128, 0);
    // ###################################################################


    // PARSING SERVER RESPONSE
    // ###################################################################
    string aux(input_buffer);
    j = json::parse(aux);
    j["idx"].get_to(player_idx);
    // ###################################################################


    // INTERPRETING SERVER RESPONSE
    // ###################################################################
    if(player_idx == -1)
    {
        // printf("[main thread] The server is currently full! Try again in a few secs!\n");
        return 0;
    }
    //else
        // printf("[main thread] You have successfully joined the server! Your index is %d!\n", player_idx);
    // ###################################################################


    // CREATING A THREAD TO HANDLE DATA RECEIVED FROM SERVER
    // ###################################################################
    // printf("[main thread] Creating game_recv_thread.\n");
    std::thread game_recv_thread(game_recv_func, socket_fd, game, player_idx);
    // ###################################################################


    // MAIN THREAD WILL BE RESPONSIBLE FOR SENDING KEYBOARD DATA TO SERVER
    // ###################################################################
    while(alive)
    {
        string buffer;
        if(keyboard->is_there_a_new_key() == true)
        {
            // printf("[main_thread] I have a new key to be sent!\n");
            buffer = keyboard->serialize();
            // printf("[main_thread] %s\n", buffer.c_str());
            send(socket_fd, buffer.c_str(), 128, 0);
        }
    }
    // ###################################################################

    game_recv_thread.join();

    // STOPING OBJECTS
    // ###################################################################
    screen->stop();
    printf("[main_thread] You have either died or quit. Please press ENTER to leave the program.\n");
    keyboard->stop();
    // ###################################################################

    close(socket_fd);
    return 0;
}
