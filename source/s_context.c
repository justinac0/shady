#include "shady.h"

#include "s_internal.h"

/* Interal Shady context */
TShadyContext* context = NULL;

int shady_init(void) {
    context = (TShadyContext*) malloc(sizeof (TShadyContext));
    if (!context) {
        return SHADY_INIT_FAILURE;
    }

    /* create surface for our shaders */
    context->surface = s_internal_surface_create();

    return SHADY_INIT_SUCCESS;
}

void shady_terminate(void) {
    s_internal_program_destroy(context->shader_program);
}

int shady_load(const char* vertex_path, const char* fragment_path) {
    GLuint vertex_shader;
    GLuint fragment_shader;

    char* vertex_source   = NULL;
    char* fragment_source = NULL;

    /* load shaders */
    vertex_source   = s_internal_read_file(vertex_path);
    fragment_source = s_internal_read_file(fragment_path);

    if (!vertex_source | !fragment_source) return 0; /* failure */

    /* create shaders from source */
    vertex_shader   = s_internal_shader_create(vertex_source,   GL_VERTEX_SHADER);
    fragment_shader = s_internal_shader_create(fragment_source, GL_FRAGMENT_SHADER);

    free(vertex_source);
    free(fragment_source);

    /* create shader program */
    context->shader_program = s_internal_program_create(vertex_shader, fragment_shader);

    if (vertex_shader           == 0 ||
        fragment_shader         == 0 ||
        context->shader_program == 0) {
        return SHADY_OPENGL_ERROR;
    }

    s_internal_shader_destroy(vertex_shader);
    s_internal_shader_destroy(fragment_shader);

    return SHADY_OPENGL_FINE; /* success */
}

void shady_update(void) {
    /* enable shader program */
    glUseProgram(context->shader_program);

    /* prepare and draw surface */
    glBindBuffer(GL_ARRAY_BUFFER, context->surface);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
}

void shady_send_uniforms(float w, float h, float mx, float my, float t) {
    glUniform1f(glGetUniformLocation(context->shader_program, "u_ScreenResolution_x"), w);
    glUniform1f(glGetUniformLocation(context->shader_program, "u_ScreenResolution_y"), h);
    glUniform1f(glGetUniformLocation(context->shader_program, "u_Mouse_x"), mx);
    glUniform1f(glGetUniformLocation(context->shader_program, "u_Mouse_y"), my);
    glUniform1f(glGetUniformLocation(context->shader_program, "u_Time"), t);
}
