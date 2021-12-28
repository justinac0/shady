#ifndef _S_INTERNAL_H_
#define _S_INTERNAL_H_

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <glad.h>

/* ---------- File I/O -------- */

#define MAX_PATH_LENGTH 128


extern char* s_internal_read_file(const char* file_path);

#if !defined(_WIN32)
#include <dirent.h>

typedef struct {
    char* vertex_path;
    char* fragment_path;
} DirShaderInfo;

extern DirShaderInfo s_internal_dir_file_names(const char* file_path);

#endif

/* ---------- Graphics -------- */

typedef struct {
    GLuint shader_program;
    GLuint surface;
} ShadyContext;

extern GLuint   s_internal_shader_create(const char* source, GLuint target);
extern void     s_internal_shader_destroy(GLuint shader);
extern GLuint   s_internal_program_create(GLuint vertex, GLuint fragment);
extern void     s_internal_program_destroy(GLuint program);
extern GLuint   s_internal_surface_create(void);

#endif
