#include <stdio.h>
#include <kc.h>

float vertices[] = {
    // Vertex cords     Colors
    -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.0f,  0.5f, 0.0f,  0.0f,  0.0f,  1.0f
};

uint indices[] = {
    0, 1, 2
};

int main() {
    renderInit(800, 600, false);

    shader_t my_shader = loadShader(".krabbacraft/res/shaders/vertex.glsl",".krabbacraft/res/shaders/fragment.glsl");

    uint vbo, vao, ebo;

    // Create VAO, VBO and EBO
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!renderWindowShouldClose) {
        renderBeginDrawing();
            renderFillBackground(BLACK);

            renderBeginShader(my_shader);

                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            renderEndShader();

        renderEndDrawing();
    }
    renderTerminate();
    return 0;
}
