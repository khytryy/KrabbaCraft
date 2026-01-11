#include <stdio.h>
#include <kc.h>

#include <cglm/cglm.h>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

int main() {
    renderInit(800, 800, false);

    shader_t my_shader = loadShader(".krabbacraft/res/shaders/vertex.glsl",".krabbacraft/res/shaders/fragment.glsl");

    glEnable(GL_DEPTH_TEST);

    uint vbo, vao;

    // Create VAO, VBO and EBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    // UV coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    image_t krabba = loadImage(".krabbacraft/res/images/KinesiskaKrabban.jpeg");
    image_t grass = loadImage(".krabbacraft/res/images/grass.jpeg");

    texture_t krabba_tex = createTextureFromImage(krabba);
    texture_t grass_tex = createTextureFromImage(grass);

    mat4 proj, model, view;
    glm_perspective(glm_rad(45.0f), (float)render_width / (float)render_height, 0.1f, 1000.0f, proj);

    glm_mat4_identity(view);
    glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

    shaderSetInt(my_shader, "texture1", 0);

    tarInit();

    while (!renderWindowShouldClose()) {
        tarOnTick((float)glfwGetTime());

        renderBeginDrawing();
            renderFillBackground(BLACK);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, krabba_tex.id);

            renderBeginShader(my_shader);

                shaderSetMat4(my_shader, "projection", proj);
                shaderSetMat4(my_shader, "view", view);
                shaderSetMat4(my_shader, "model", model);

                glm_mat4_identity(model);
                glm_rotate(model, (float)glfwGetTime() * glm_rad(50.0f), (vec3){1.0f, 1.0f, -0.5f});

                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            renderEndShader();

        renderEndDrawing();
    }
    renderTerminate();
    return 0;
}
