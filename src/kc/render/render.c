#include <kc/render/render.h>

GLFWwindow *render_window = null;
double previous_time;

int render_width, render_height;

void renderErrorCallback(int error, const char *description) {
    dbgWrite("GLFW", LOG_LEVEL_FATAL_ERROR, "[GLFW/ERROR %d] %s\n", error, description);
}

void renderFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    render_width = width;
    render_height = height;
}

void renderInit(int width, int height, bool fullscreen) {
    render_width = width;
    render_height = height;

    glfwSetErrorCallback(renderErrorCallback);

    if (!glfwInit()) {
        dbgWrite("GLFW", LOG_LEVEL_FATAL_ERROR, "glfwInit() returned false\n");
        abort();
    }

    // Set the OpenGL version to core 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    render_window = glfwCreateWindow(width, height, GAME_VER, fullscreen ? glfwGetPrimaryMonitor() : null, null);
    if (render_window == null) {
        dbgWrite("GLFW", LOG_LEVEL_FATAL_ERROR, "Render window is NULL\n");
        abort();
    }

    glfwMakeContextCurrent(render_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        dbgWrite("GLAD", LOG_LEVEL_ERROR, "Failed to initialize GLAD\n");
        abort();
    }

    int fb_w, fb_h;
    glfwGetFramebufferSize(render_window, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);

    glfwSetFramebufferSizeCallback(render_window, renderFramebufferSizeCallback);

    const GLubyte *vendor           = glGetString(GL_VENDOR);
    const GLubyte *renderer         = glGetString(GL_RENDERER);
    const GLubyte *gl_version       = glGetString(GL_VERSION);
    const GLubyte *glsl_ver         = glGetString(GL_SHADING_LANGUAGE_VERSION);

    dbgWrite("RENDER", LOG_LEVEL_INFO, " OpenGL device information:\n");
    dbgWrite("RENDER", LOG_LEVEL_INFO, "      Vendor:     %s\n", vendor);
    dbgWrite("RENDER", LOG_LEVEL_INFO, "      Renderer:   %s\n", renderer);
    dbgWrite("RENDER", LOG_LEVEL_INFO, "      OpenGL:     %s\n", gl_version);
    dbgWrite("RENDER", LOG_LEVEL_INFO, "      GLSL:       %s\n", glsl_ver);

    previous_time = glfwGetTime(); 
}

void renderTerminate(void) {
    glfwTerminate();
}

void renderBeginDrawing(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderEndDrawing(void) {
    glfwSwapBuffers(render_window);
    glfwPollEvents();
}

void renderFillBackground(color_t color) {
    glClearColor((float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderBeginShader(shader_t shader) {
    useShader(shader);
}

void renderEndShader(void) {
    glUseProgram(0);
}

bool renderWindowShouldClose(void) {
    return glfwWindowShouldClose(render_window);
}