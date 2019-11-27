#ifndef KBOARD_RECV_FUNC_HPP
#define KBOARD_RECV_FUNC_HPP

#include "action.hpp"
#include "keyboard.hpp"

void kboard_recv_func(int connection_fd, int player_idx, Model::Keyboard * keyboard, Controller::Action * action);

#endif
