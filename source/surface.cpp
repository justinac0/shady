#include "surface.hpp"


GLuint create_quad(int x, int y, float w, float h) {
    float xoffs = 2*x + w;
    float yoffs = 2*y + h;

    float quad[] = {
		(-w) - (1 - xoffs), ( h) + (1 - yoffs), // tl
		( w) - (1 - xoffs), ( h) + (1 - yoffs), // tr
		( w) - (1 - xoffs), (-h) + (1 - yoffs), // br
		(-w) - (1 - xoffs), (-h) + (1 - yoffs)  // bl
	};

    int ints[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint ido;
	glGenBuffers(1, &ido);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ido);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ints), ints, GL_STATIC_DRAW);

    GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return vao;
}


shady::Surface::Surface() {}


shady::Surface::~Surface() {}


void shady::Surface::load(std::string vertexPath, std::string fragmentPath) {
    this->vertex = Shader::load(vertexPath.c_str(), GL_VERTEX_SHADER);
    this->fragment = Shader::load(fragmentPath.c_str(), GL_FRAGMENT_SHADER);
    this->program = Shader::create_program(vertex, fragment);
    this->surface = create_quad(0, 0, 640, 480);
}


void shady::Surface::begin_draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    glUseProgram(this->program);
}


void shady::Surface::end_draw() {
    glBindVertexArray(this->surface);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}


GLuint shady::Surface::get_program_id() {
    return this->program;
}