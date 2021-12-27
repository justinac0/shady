#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdbool.h>

#include <glad.h>
#include <GLFW/glfw3.h>

/* ---------- GLFW Handling -------- */

GLFWwindow* window_create(GLFWkeyfun key_callback);
void window_destroy(GLFWwindow* window);
bool window_should_close(GLFWwindow* window);

void window_update(GLFWwindow* window);
void window_clear(void);

#endif
