#include <thread>

#include <stdio.h>
#include <string.h>
#include <unistd.h>     // #
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // #
#include <arpa/inet.h>  // #

#include "kboard_recv_func.hpp"

void kboard_recv_func(int connection_fd, int player_idx, Model::Keyboard * keyboard, Controller::Action * action)
{
    char input_buffer[128];

    printf("[kboard_recv_thread] Hi! I'll be processing player %d's keyboard data!\n", player_idx);

    while(true)
    {
        // WAITING FOR KEYBOARD DATA
        // #####################################################################
        if(recv(connection_fd, input_buffer, 128, 0) <= 0)  break;
        //printf("[kboard_recv_thread] Player %d sent: %s\n", player_idx, input_buffer);
        // #####################################################################


        // UNSERIALIZING KEYBOARD DATA
        // #####################################################################
        keyboard->unserialize(input_buffer);
        // #####################################################################


        // PROCESSING KEYBOARD DATA
        // #####################################################################
        switch(keyboard->get_key())
        {
            case 'w':
            case 'W':
                // Player moves upwards, if possible
                action->perform(Controller::ActionType::MOVE_UP, player_idx);
                break;
            case 'd':
            case 'D':
                // Player moves rightwards, if possible
                action->perform(Controller::ActionType::MOVE_RIGHT, player_idx);
                break;
            case 's':
            case 'S':
                // Player moves downwards, if possible
                action->perform(Controller::ActionType::MOVE_DOWN, player_idx);
                break;
            case 'a':
            case 'A':
                // Player move leftwards, if possible
                action->perform(Controller::ActionType::MOVE_LEFT, player_idx);
                break;
            case 'j':
            case 'J':
                // Player spawns bomb in its orientation, if possible
                action->perform(Controller::ActionType::SPAWN_BOMB, player_idx);
                break;
        }
        // #####################################################################
    }

    printf("[kboard_recv_thread] Player %d has either died or quit the game!\n", player_idx);
    close(connection_fd);
}
