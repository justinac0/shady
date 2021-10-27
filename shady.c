#include "shady.h"

s_Shader s_create_shader(const int8_t* src, uint32_t target) {
    s_Shader shader;
    shader = glCreateShader(target);

	glShaderSource(shader, 1, &src, 0);
	glCompileShader(shader);

	int compile_status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE) {
		uint32_t length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		int8_t* log = (char*) calloc(length, sizeof(int8_t));

		glGetShaderInfoLog(shader, length, &length, &log[0]);
		glDeleteShader(shader);

        fprintf(stderr, "Compilation Error: %s.\n", log);
		free(log);
	}

	return shader;
}

s_Program s_create_program(s_Shader vertex, s_Shader fragment) {
    s_Program program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);

    int32_t link_status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        uint32_t length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        int8_t* log = (char*) calloc(length, sizeof(int8_t));
        glGetProgramInfoLog(program, length, &length, &log[0]);

        glDeleteProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        fprintf(stderr, "Linking Error: %s\n", log);

        free(log);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void s_destroy_program(s_Program id) {
    glDeleteProgram(id);
}

uint32_t s_create_surface() {
    float quad[] = {
		-1, 1,
		 1, 1,
		 1,-1
		-1,-1
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    return buffer; 
}

void s_update_surface(uint32_t buffer, uint32_t program) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_QUADS, 0, 4);
}
