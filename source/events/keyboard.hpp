#pragma once

#include "event_base.hpp"

namespace shady {

    class KeyboardEvent : public EventBase {
        private:
            EventType type;
            int key;
        public:
            KeyboardEvent(EventType type, int key);
            EventType get_type();
    };

}