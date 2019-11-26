#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>

#include "action_type.hpp"
#include "action.hpp"
#include "element.hpp"
#include "game.hpp"
#include "game_send_func.hpp"
#include "keyboard.hpp"
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
    char input_buffer[128];

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

    // ########## MIGHT BE USED ON SERVER ##########
    Model::Keyboard * keyboard = new Model::Keyboard();
    // ########## MIGHT BE USED ON SERVER ##########

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
    /*
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
    {
        borders.push_back(new Model::Element("../assets/sprites/border.sprite", Model::ElementType::GROUND));
        (borders.back())->update(3 + 5 * (i / 13), 25 + 7 * (i % 13));
    }
    */

    // Intializing objects
    // game->init();
    // action->init();
    /*
    screen->init();
    */

    // ########## MIGHT BE USED ON SERVER ##########
    keyboard->init();
    // ########## MIGHT BE USED ON SERVER ##########

    // TODO: Call this from Screen object
    /*
    for(int i = 0; i < 91; i++)
        borders[i]->render();
    */

    std::thread new_thread(game_send_func, connection_fd, game);

    while(!finish)
    {
        bool quit = false;
        string buffer_in, buffer_out;

        // Refreshing the screen at most 200 times per second
        std::this_thread::sleep_for (std::chrono::milliseconds(200));
        // TODO: Call this from Screen object

        /* ########## REMOVE ##########
        game->render();
        buffer_out = game->serialize();
        send(connection_fd, buffer_out.c_str(), 512, 0);
        */ // ########## REMOVE ##########


        /* ########## REMOVE ##########
        char c = input_buffer[0];
        move(0, 0); echochar(c);
        */ // ########## REMOVE ##########

        // cout << input_buffer << endl;

        recv(connection_fd, input_buffer, 128, 0);
        keyboard->unserialize(input_buffer);

        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
        // If there's a new key to be processed ('true')
        /*
        if(keyboard->get_key(&c) == true)
        {
        */
        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########

        switch(keyboard->get_key())
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
            case 'q':
            case 'Q':
                quit = true;
                break;
        }

        // Quits the game
        if(quit == true)  break;


        // ########## DEBUG ##########
        //move(0, 0);
        //printw(buffer.c_str());
        // ########## DEBUG ##########

        // ########## DEBUG ##########
        // game->unserialize(buffer);
        // game->render();
        // ########## DEBUG ##########

        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
        /*
        }
        */
        // ########## NOT GOING TO BE USED ON SERVER (AT LEAST BY NOW) ##########
    }

    close(connection_fd);
    close(socket_fd);

    // ########## MIGHT BE USED ON SERVER ##########
    keyboard->stop();
    // ########## MIGHT BE USED ON SERVER ##########
    screen->stop();
    // action->stop();
    // game->stop();

    return 0;
}
