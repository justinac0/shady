#ifndef SHADY_H
#define SHADY_H

/* Standard Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* OpenGL Extension Loading */
#include <glad.h>

/* ---------- Error Defines -------- */
#define SHADY_INIT_FAILURE 0
#define SHADY_INIT_SUCCESS 1

/* TODO: defs for different opengl errors*/
#define SHADY_OPENGL_FINE  2
#define SHADY_OPENGL_ERROR 3


/* ---------- Handlers -------- */

typedef struct {
    GLuint shader_program;
    GLuint surface;
} TShadyContext;


/* ---------- Shady Handling -------- */

extern int  shady_init(void);
extern void shady_terminate(void);
extern int  shady_load(const char* vertex_path, const char* fragment);
extern void shady_update(void);
extern void shady_send_uniforms(float w, float h, float mx, float my, float t);


#endif
