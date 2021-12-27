#ifndef _S_INTERNAL_H_
#define _S_INTERNAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <glad.h>

/* ---------- File I/O -------- */

extern char*  s_internal_read_file(const char* file_path);

/* ---------- OpenGL Abstractions -------- */

extern GLuint s_internal_shader_create(const char* source, GLuint target);
extern void s_internal_shader_destroy(GLuint shader);

extern GLuint s_internal_program_create(GLuint vertex, GLuint fragment);
extern void s_internal_program_destroy(GLuint program);

extern GLuint s_internal_surface_create(void);

#endif
