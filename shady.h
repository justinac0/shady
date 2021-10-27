#ifndef SHADY_H
#define SHADY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <glad.h>

typedef uint32_t s_Shader;
typedef uint32_t s_Program;

s_Shader s_create_shader(const int8_t* src, uint32_t target);
s_Program s_create_program(s_Shader vertex, s_Shader fragment);
void s_destroy_program(s_Program id);

uint32_t s_create_surface();
void s_update_surface(uint32_t buffer, uint32_t program);

#endif // SHADY_H
