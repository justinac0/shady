#pragma once

namespace shady {
    typedef enum {
        QUIT,
        RELOAD_SHADERS,
        // PAUSE_TIME,
        // FORWARD_TIME,
        // BACKWARD_TIME,
        IO_ERROR,
        SHADER_ERROR,
        LOAD_SHADERS,
        // CREATE_PROJECT,
    } EventType;

    class EventBase {
        public:
            virtual EventType get_type();
    };

}