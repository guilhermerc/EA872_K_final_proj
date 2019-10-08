#include <iostream>

#include "keyboard_func.hpp"
#include "keyboard.hpp"

using namespace Model;

Keyboard::Keyboard()
{
    this->key = 0;
    this->processed = true;
    this->running = false;
}

Keyboard::~Keyboard()
{

}

void Keyboard::init()
{
    this->running = true;
    std::thread new_thread(keyboard_func, &(this->key), &(this->processed), &(this->running));
    // TODO: Check if this is indeed the best way of "assigning threads"
    (this->kboard_thread).swap(new_thread);
}

void Keyboard::stop()
{
    this->running = false;
    (this->kboard_thread).join();
}

bool Keyboard::get_key(char * c)
{
    bool status = false;
    if(this->processed == false)
    {
        (*c) = this->key;
        this->processed = true;
        status = true;
    }
    return status;
}
