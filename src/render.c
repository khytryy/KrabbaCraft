#include <kc/render/render.h>

GLFWwindow *render_window = null;

void renderErrorCallback(int error, const char *description) {
    fprintf(stderr, "[GLFW/ERROR %d] %s\n", error, description);
}

void renderInit(int width, int height, bool fullscreen) {

    glfwSetErrorCallback(renderErrorCallback);

    if (!glfwInit()) {
        dbgWrite("GLFW", ERROR, "Failed to initialize\n");
        abort();
    }

    // Set the OpenGL version to core 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    render_window = glfwCreateWindow(width, height, GAME_VER, fullscreen ? glfwGetPrimaryMonitor() : null, null);
    if (render_window == null) {
        dbgWrite("GLFW", ERROR, "Render window is null\n");
        abort();
    }

    glfwMakeContextCurrent(render_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        dbgWrite("GLAD", ERROR, "Failed to initialize\n");
        abort();
    }

    glViewport(0, 0, width, height);

    const GLubyte *vendor           = glGetString(GL_VENDOR);
    const GLubyte *renderer         = glGetString(GL_RENDERER);
    const GLubyte *gl_version       = glGetString(GL_VERSION);
    const GLubyte *glsl_ver         = glGetString(GL_SHADING_LANGUAGE_VERSION);

    dbgWrite("RENDER", INFO, " OpenGL device information:\n");
    dbgWrite("RENDER", INFO, "      Vendor:     %s\n", vendor);
    dbgWrite("RENDER", INFO, "      Renderer:   %s\n", renderer);
    dbgWrite("RENDER", INFO, "      OpenGL:     %s\n", gl_version);
    dbgWrite("RENDER", INFO, "      GLSL:       %s\n", glsl_ver);
}

void renderTerminate(void) {
    glfwTerminate();
}

void renderBeginDrawing(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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
void renderEndShader() {
    glUseProgram(0);
}