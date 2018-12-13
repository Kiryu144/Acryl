R"(
#version 330 core
in vec2 _uv;

out vec4 color;

uniform sampler2D sampler;

void main() {
    color = texture(sampler, _uv);
}
)"