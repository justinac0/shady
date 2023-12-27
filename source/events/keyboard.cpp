#include "keyboard.hpp"


shady::KeyboardEvent::KeyboardEvent(EventType type, int key) {
    this->type = type;
    this->key = key;
}


shady::EventType shady::KeyboardEvent::get_type() {
    return this->type;
}