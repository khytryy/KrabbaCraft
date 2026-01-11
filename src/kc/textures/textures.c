#define STB_IMAGE_IMPLEMENTATION
#include <kc/textures/textures.h>

image_t loadImage(const char *path) {
    image_t image;

    stbi_set_flip_vertically_on_load(1);
    image.data = stbi_load(path, &image.width, &image.height, &image.channels, 0);
    if (!image.data) {
        dbgWrite("TEXTURES", LOG_LEVEL_FATAL_ERROR, "Image data is null.\n");
        abort();
    }

    return image;
}

texture_t createTextureFromImage(image_t image) {
    texture_t texture;

    uint format = (image.channels == 4) ? GL_RGBA : GL_RGB;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    // Tell OpenGL to repeat the texture if it falls outside of the range
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width, image.height, 0, format, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return texture;
}

void freeImage(image_t image) {
    image.channels, image.width, image.height = 0;
    stbi_image_free(image.data);
}