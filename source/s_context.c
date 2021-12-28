#include "shady.h"

#include "s_internal.h"

/* Interal Shady context */
ShadyContext* context = NULL;

int shady_init(void) {
    context = (ShadyContext*) malloc(sizeof (ShadyContext));
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
    if (context->shader_program != 0)
        s_internal_program_destroy(context->shader_program);

    GLuint vertex_shader    = 0;
    GLuint fragment_shader  = 0;

    char* vertex_source   = NULL;
    char* fragment_source = NULL;

    /* load shaders */
    vertex_source   = s_internal_read_file(vertex_path);
    fragment_source = s_internal_read_file(fragment_path);

    if (!vertex_source || !fragment_source) return SHADY_OPENGL_ERROR; /* failure */

    /* create shaders from source */
    vertex_shader   = s_internal_shader_create(vertex_source,   GL_VERTEX_SHADER);
    fragment_shader = s_internal_shader_create(fragment_source, GL_FRAGMENT_SHADER);

    free(vertex_source);
    free(fragment_source);

    /* create shader program */
    context->shader_program = s_internal_program_create(vertex_shader, fragment_shader);

    if (vertex_shader == 0 || fragment_shader == 0 || context->shader_program == 0)
        return SHADY_OPENGL_ERROR;

#ifdef DEBUG
    printf("vs: %d\nfs: %d\nsp: %d\n\n", vertex_shader, fragment_shader, context->shader_program);
#endif

    s_internal_shader_destroy(vertex_shader);
    s_internal_shader_destroy(fragment_shader);

    return SHADY_OPENGL_FINE;
}

#if !defined(_WIN32)
int shady_load_folder(const char* path) {
    DirShaderInfo dir_info = s_internal_dir_file_names(path);

    int status = shady_load(dir_info.vertex_path, dir_info.fragment_path);

    free(dir_info.vertex_path);
    free(dir_info.fragment_path);

    return status;
}
#endif

void shady_update(void) {
    /* enable shader program */
    glUseProgram(context->shader_program);

    /* prepare and draw surface */
    glBindBuffer(GL_ARRAY_BUFFER, context->surface);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
}

void shady_send_vec2f(float x, float y, const char* name) {
    glUniform2fv(glGetUniformLocation(context->shader_program, name), 1, (float[2]){x, y});
}

void shady_send_int(int i, const char* name) {
    glUniform1i(glGetUniformLocation(context->shader_program, name), i);
}

void shady_send_float(float f, const char* name) {
    glUniform1f(glGetUniformLocation(context->shader_program, name), f);
}
