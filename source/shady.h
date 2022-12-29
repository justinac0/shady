#ifndef SHADY_H
#define SHADY_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#ifdef SHADY_INCLUDE_ALL
#define SHADY_CORE
#define SHADY_UI
#endif


typedef struct ShadyInfo {
    GLuint programID;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint surface;
} ShadyInfo;


/* ------ Init -------- */
bool shady_init(int width, int height);
void shady_terminate(void);
bool shady_is_open(void);
void shady_update(void);


/* ------ Shady Core -------- */
#ifdef SHADY_CORE

void shady_load_default(void);
void shady_load(const char *vertexShader, const char *fragmentShader);
void shady_load_folder(const char *folder);
void shady_draw(void);

#endif // SHADY_CORE


/* ------ Shady UI -------- */
#ifdef SHADY_UI

void shady_ui_init(const char* fontPath);
void shady_ui_terminate(void);

void shady_ui_begin();
void shady_ui_end();

void shady_ui_char(const char c, int x, int y);
void shady_ui_text(const char *text, int x, int y);

#endif // SHADY_UI


#endif // SHADY_H
