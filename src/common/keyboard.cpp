#include "json.hpp"
using json = nlohmann::json;

#include "keyboard_func.hpp"
#include "keyboard.hpp"

using namespace Model;

// CHECKED
Keyboard::Keyboard()
{
    this->key = 0;
    this->processed = true;
    this->running = false;
}

// CHECKED
Keyboard::~Keyboard()
{
    this->stop();
}

// CHECKED
void Keyboard::init()
{
    this->running = true;
    std::thread keyboard_thread(keyboard_func, &(this->key), &(this->processed), &(this->running));
    /* TODO: Check if this is indeed the best way of "assigning threads" */
    (this->kboard_thread).swap(keyboard_thread);
}

// CHECKED
void Keyboard::stop()
{
    this->running = false;
    this->kboard_thread.join();
}

// CHECKED
/* Returns 'true' if a non-processed key is buffered ('false' otherwise). */
bool Keyboard::is_there_a_new_key()
{
    return !this->processed;
}

// CHECKED
char Keyboard::get_key()
{
    return this->key;
}

// CHECKED
std::string Keyboard::serialize()
{
    json j;

    j["key"] = this->key;
    this->processed = true;

    return j.dump();
}

void Keyboard::unserialize(char * buffer)
{
    json j;

    j = json::parse(buffer);
    j["key"].get_to(this->key);
}
