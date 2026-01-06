#include <stdio.h>
#include <kc.h>

float vertices[] = {
    // Vertex cords     RGB              UV
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // Top right
     0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // Top left
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // Bottom left
     0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f     // Bottom right
};

uint indices[] = {
    1, 3, 2,
    0, 2, 1
};

int main() {
    renderInit(800, 800, false);

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

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // UV coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    image_t krabba = loadImage(".krabbacraft/res/images/KinesiskaKrabban.jpeg");

    texture_t krabbaTex = createTextureFromImage(krabba);

    while (!renderWindowShouldClose()) {
        renderBeginDrawing();
            renderFillBackground(BLACK);

            glBindTexture(GL_TEXTURE_2D, krabbaTex.id);
            renderBeginShader(my_shader);

                shaderSetInt(my_shader, "texture1", 0);
                glBindVertexArray(vao);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            renderEndShader();

        renderEndDrawing();
    }
    renderTerminate();
    return 0;
}
