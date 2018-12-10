R"(
#version 330 core
in vec2 _uv;
flat in int _instanceID;

out vec4 color;

uniform sampler2D sampler[16];

void main() {
    color = texture(sampler[_instanceID], _uv);
}
)"