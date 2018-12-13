R"(
#version 330 core
layout (location = 0) in vec2 vertice;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 atlasData;

out vec2 _uv;

uniform mat4 mvp;
uniform float rowCount;

void main() {
    vec2 offset = vec2(mod(atlasData.z, rowCount)/rowCount, floor(int(atlasData.z) / rowCount)/rowCount);


    gl_Position = mvp * vec4(atlasData.x + vertice.x, atlasData.y + vertice.y, 0.0, 1.0);
    _uv = offset + (uv / vec2(rowCount));
}
)"