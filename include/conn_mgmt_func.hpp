#ifndef CONN_MGMT_FUNC_HPP
#define CONN_MGMT_FUNC_HPP

#include "action.hpp"
#include "keyboard.hpp"

void conn_mgmt_func(int socket_fd, Model::Keyboard * keyboard, Controller::Action * action);

#endif
