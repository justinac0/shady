#ifndef SHADY_H
#define SHADY_H

/* Standard Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* OpenGL Extension Loading */
#include <glad/glad.h>

/* ---------- Error Defines -------- */
#define SHADY_INIT_FAILURE 0
#define SHADY_INIT_SUCCESS 1
#define SHADY_OPENGL_FINE  2
#define SHADY_OPENGL_ERROR 3

/* ---------- Shady Handling -------- */

/**/
extern int  shady_init(void);

/**/
extern void shady_terminate(void);

/**/
extern int  shady_load(const char* vertex_path, const char* fragment);

#if !defined(_WIN32)
/**/
extern int  shady_load_folder(const char* path);
#endif

/**/
extern void shady_update(void);

/**/
extern void shady_send_vec2f(float x, float y, const char* name);

/**/
extern void shady_send_int(int i, const char* name);

/**/
extern void shady_send_float(float f, const char* name);


#endif
