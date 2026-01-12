#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTileData;

out vec2 texPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform int atlasWidth;
uniform int tileWidth;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    int aCornerID = int(aTileData.y);
    int tileIndex = int(aTileData.x);

    float localU = (aCornerID == 1 || aCornerID == 2) ? 1.0 : 0.0;
    float localV = (aCornerID == 2 || aCornerID == 3) ? 1.0 : 0.0;

    float normalizedTileWidth = float(tileWidth) / float(atlasWidth);

    float finalU = (float(tileIndex) * normalizedTileWidth) + (localU * normalizedTileWidth);
    float finalV = localV;

    texPos = vec2(finalU, finalV);
}