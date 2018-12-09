R"(
#version 330 core
layout (location = 0) in vec2 vertice;
layout (location = 1) in vec2 uv;

out vec2 _uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertice.xy, 0.0, 1.0);
    _uv = uv;
}
)"