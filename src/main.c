#include <stdio.h>
#include <kc.h>

float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

uint indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main() {
    renderInit(800, 600, false);

    shader_t my_shader = loadShader(".krabbacraft/res/shaders/vertex.glsl",".krabbacraft/res/shaders/fragment.glsl");

    uint vbo, vao;

    // Create VBO and VAO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind everything to the VAO
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!renderWindowShouldClose) {
        renderBeginDrawing();
            renderFillBackground(BLACK);

            glBindVertexArray(vao);
            renderBeginShader(my_shader);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            renderEndShader();

        renderEndDrawing();
    }
    renderTerminate();
    return 0;
}