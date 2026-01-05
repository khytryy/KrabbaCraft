#include <kc/shaders/shaders.h>

shader_t loadShader(const char *vertex_path, const char *fragment_path) {
    shader_t shader;

    char *vertex = loadFile(vertex_path);
    char *fragment = loadFile(fragment_path);

    shader = loadShaderMem(vertex, fragment);

    return shader;
}
shader_t loadShaderMem(const char *vertex, const char *fragment) {
    shader_t shader;

    // Compile the vertex shader
    uint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex, null);
    glCompileShader(vertex_shader);

    // Check for any compile errors
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, null, info_log);

        dbgWrite("SHADERS", ERROR, "Vertex shader compilation error: %s\n", info_log);
        abort();
    }

    // Do the same thing for the fragment shader
    uint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment, null);
    glCompileShader(fragment_shader);

    // Check for errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, null, info_log);

        dbgWrite("SHADERS", ERROR, "Fragment shader compilation error: %s\n", info_log);
        abort();
    }

    uint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    // Check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, null, info_log);

        dbgWrite("SHADERS", ERROR, "Program linking error: %s\n", info_log);
        abort();
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    shader.program = program;

    dbgWrite("SHADERS", INFO, "Shader loaded!\n");
    return shader;
}

void useShader(shader_t shader) {
    glUseProgram(shader.program);
}