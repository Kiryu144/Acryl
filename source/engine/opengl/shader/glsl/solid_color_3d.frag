R"(
#version 330 core
out vec4 color;

uniform vec4 _color;

void main() {
    color = _color;
}
)"