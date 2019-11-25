#include <ncurses.h>

#include "json.hpp"
using json = nlohmann::json;

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
    this->stop();
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
    this->kboard_thread.join();
}

// Returns 'true' if a non-processed key is buffered, 'false' otherwise.
bool Keyboard::is_there_a_new_key()
{
    return !this->processed;
}

// ########## DEBUG PURPOSES ONLY ##########
char Keyboard::get_key()
{
    return this->key;
}
// ########## DEBUG PURPOSES ONLY ##########

std::string Keyboard::serialize()
{
    json j;

    j["key"] = this->key;
    this->processed = true;

    // ########## DEBUG PURPOSES ONLY ##########
    move(1, 19); printw("                    ");
    move(1, 19); printw(j.dump().c_str());
    // ########## DEBUG PURPOSES ONLY ##########

    return j.dump();
}

void Keyboard::unserialize(char * buffer)
{
    json j;
    j = json::parse(buffer);
    j["key"].get_to(this->key);
}
