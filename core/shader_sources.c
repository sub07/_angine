#include "shader_sources.h"

char const *const texture_batch_vertex_shader_source =
    "#version 460\n"
    "layout(location = 0) in vec2 vertexPosition;\n"
    "layout(location = 1) in vec2 texturePosition;\n"
    "layout(location = 2) in vec4 color;\n"
    "out vec2 transformedTexturePosition;\n"
    "out vec4 tint;\n"
    "uniform vec2 viewportSize;\n"
    "void main() {\n"
    "vec2 workingVec = vertexPosition;\n"
    "workingVec.x = workingVec.x * (2 / viewportSize.x) - 1;\n"
    "workingVec.y = workingVec.y * -(2 / viewportSize.y) + 1;\n"
    "gl_Position = vec4(workingVec, 0.0, 1.0);\n"
    "transformedTexturePosition = texturePosition;\n"
    "tint = color;\n"
    "}\n";

char const *const texture_batch_fragment_shader_source =
    "#version 460\n"
    "in vec2 transformedTexturePosition;\n"
    "in vec4 tint;\n"
    "uniform sampler2D textureUnit;\n"
    "out vec4 finalPixelColor;\n"
    "void main() {\n"
    "finalPixelColor = texture(textureUnit, transformedTexturePosition) * tint;\n"
    "}\n";
