#include <ncurses.h>
#include <thread>
#include <vector>

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
    int socket_fd;
    struct sockaddr_in target;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created!\n");

    target.sin_family = AF_INET;
    target.sin_port = htons(3001);
    inet_aton("127.0.0.1", &(target.sin_addr));

    printf("Attempting to connect to server...\n");
    while(connect(socket_fd, (struct sockaddr*) &target, sizeof(target)) != 0)
    {
        printf("Connection problem. Trying again in 1 sec...\n");
        sleep(1);
    }
    printf("Connection to server stablished!\n");

    sleep(2);
    // ########## SOCKET RELATED CODE ##########

    // Model objects
    // Although these objects have some View/Controller methods, they are
    // intended to be used as interfaces to objects related to these components

    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
    /*
    Model::Game * game = new Model::Game("../assets/map.config");
    */
    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

    Model::Keyboard * keyboard = new Model::Keyboard();

    // View objects
    // Maximum height: 44
    // Maximum width: 143
    View::Screen * screen = new View::Screen(44, 143);

    // Controller objects
    /* ## Not gonna be used ##
    Controller::Action * action = new Controller::Action(game);
    */

    // TODO: REMOVE HARDCODED VALUES
    // TODO: Encapsulate this inside Game class
    // TODO: Renderize efficiently (only load the border sprite once)
    // Allocating borders

    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
    /*
    vector<Model::Element *> borders;
    for(int i = 0; i < 91; i++)
    {
        borders.push_back(new Model::Element("../assets/sprites/border.sprite"));
        (borders.back())->update(3 + 5 * (i / 13), 25 + 7 * (i % 13));
    }
    */
    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########


    // Intializing objects
    // game->init();
    // action->init();
    screen->init();
    keyboard->init();

    // TODO: Call this from Screen object

    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
    /*
    for(int i = 0; i < 91; i++)
        borders[i]->render();
    */
    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

    move(0, 0);
    printw("The pressed key is ");
    attron(A_BOLD);

    while(!finish)
    {
        char c;
        // If there's a new key to be processed ('true')
        if(keyboard->get_key(&c) == true)
        {
            move(0, 19);
            echochar(c);
            echochar(' ');

            switch(c)
            {
                case 'w':
                case 'W':
                    // Player moves upwards, if possible

                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
                    /*
                    action->perform(Controller::ActionType::MOVE_UP);
                    */
                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

                    send(socket_fd, "w", 2, 0);

                    break;
                case 'd':
                case 'D':
                    // Player moves rightwards, if possible

                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
                    /*
                    action->perform(Controller::ActionType::MOVE_RIGHT);
                    */
                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

                    send(socket_fd, "d", 2, 0);

                    break;
                case 's':
                case 'S':
                    // Player moves downwards, if possible

                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
                    /*
                    action->perform(Controller::ActionType::MOVE_DOWN);
                    */
                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

                    send(socket_fd, "s", 2, 0);

                    break;
                case 'a':
                case 'A':
                    // Player move leftwards, if possible

                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
                    /*
                    action->perform(Controller::ActionType::MOVE_LEFT);
                    */
                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

                    send(socket_fd, "a", 2, 0);

                    break;
                case 'j':
                case 'J':
                    // Player spawns bomb in its orientation, if possible

                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
                    /*
                    action->perform(Controller::ActionType::SPAWN_BOMB);
                    */
                    // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########

                    send(socket_fd, "j", 2, 0);

                    break;
            }

            // Quits the game
            if(c == 'q' || c == 'Q')
            {
                send(socket_fd, "q", 2, 0);
                break;
            }
        }

        // Refreshing the screen at most 200 times per second
        std::this_thread::sleep_for (std::chrono::milliseconds(5));
        // TODO: Call this from Screen object

        // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
        /*
        game->render();
        */
        // ########## NOT GOING TO BE USED ON CLIENT (AT LEAST BY NOW) ##########
    }

    close(socket_fd);

    keyboard->stop();
    screen->stop();
    // action->stop();
    // game->stop();

    return 0;
}
