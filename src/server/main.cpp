#include <ncurses.h>
#include <thread>
#include <vector>

#include "action_type.hpp"
#include "action.hpp"
#include "element.hpp"
#include "game.hpp"
#include "screen.hpp"

#include <stdio.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

using namespace std;

bool finish = false;

int main()
{
    // ########## SOCKET RELATED CODE ##########
    int socket_fd, connection_fd;
    struct sockaddr_in myself, client;
    socklen_t client_size = (socklen_t) sizeof(client);
    char input_buffer[10];

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created!\n");

    myself.sin_family = AF_INET;
    myself.sin_port = htons(3001);
    inet_aton("127.0.0.1", &(myself.sin_addr));

    printf("Attempting to open port 3001...\n");

    while(bind(socket_fd, (struct sockaddr*)&myself, sizeof(myself)) != 0)
    {
        printf("Problems while attempting to open port 3001. Trying again in 1 sec...\n");
        sleep(1);
    }

    printf("Port 3001 opened!\n");

    listen(socket_fd, 2);
    printf("Listening on port 3001...\n");

    printf("Waiting for a connection request...\n");
    connection_fd = accept(socket_fd, (struct sockaddr*) &client, &client_size);
    printf("A client has connected with me!\n");

    sleep(2);
    // ########## SOCKET RELATED CODE ##########

    // Model objects
    // Although these objects have some View/Controller methods, they are
    // intended to be used as interfaces to objects related to these components
    Model::Game * game = new Model::Game("../assets/map.config");

    // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
    /*
    Model::Keyboard * keyboard = new Model::Keyboard();
    */
    // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########

    // View objects
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);

    // Controller objects
    Controller::Action * action = new Controller::Action(game);

    // TODO: REMOVE HARDCODED VALUES
    // TODO: Encapsulate this inside Game class
    // TODO: Renderize efficiently (only load the border sprite once)
    // Allocating borders
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
    {
        borders.push_back(new Model::Element("../assets/sprites/border.sprite", Model::ElementType::GROUND));
        (borders.back())->update(3 + 5 * (i / 13), 25 + 7 * (i % 13));
    }

    // Intializing objects
    // game->init();
    // action->init();
    screen->init();

    // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
    /*
    keyboard->init();
    */
    // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########

    // TODO: Call this from Screen object
    for(int i = 0; i < 91; i++)
        borders[i]->render();

    while(!finish)
    {
        move(0, 0); echochar('-');

        // Refreshing the screen at most 200 times per second
        std::this_thread::sleep_for (std::chrono::milliseconds(5));
        // TODO: Call this from Screen object
        game->render();

        recv(connection_fd, input_buffer, 10, 0);

        char c = input_buffer[0];
        move(0, 0); echochar(c);

        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
        // If there's a new key to be processed ('true')
        /*
        if(keyboard->get_key(&c) == true)
        {
        */
        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########

        switch(c)
        {
            case 'w':
            case 'W':
                // Player moves upwards, if possible
                action->perform(Controller::ActionType::MOVE_UP);
                break;
            case 'd':
            case 'D':
                // Player moves rightwards, if possible
                action->perform(Controller::ActionType::MOVE_RIGHT);
                break;
            case 's':
            case 'S':
                // Player moves downwards, if possible
                action->perform(Controller::ActionType::MOVE_DOWN);
                break;
            case 'a':
            case 'A':
                // Player move leftwards, if possible
                action->perform(Controller::ActionType::MOVE_LEFT);
                break;
            case 'j':
            case 'J':
                // Player spawns bomb in its orientation, if possible
                action->perform(Controller::ActionType::SPAWN_BOMB);
                break;
        }

        // Quits the game
        if(c == 'q' || c == 'Q')  break;

        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
        /*
        }
        */
        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
    }

    // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
    /*
    keyboard->stop();
    */
    // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########

    close(connection_fd);
    close(socket_fd);

    screen->stop();
    // action->stop();
    // game->stop();

    return 0;
}
