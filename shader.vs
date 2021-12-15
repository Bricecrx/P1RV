#version 330 core

layout (location = 0) in vec3 Position;

uniform mat4 gScale;

out vec4 Color;

const vec4 Colors[3] = vec4[3](vec4(1,0,0,1),vec4(0,1,0,1), vec4(0,0,1,1));

void main()
{
    gl_Position = gScale * vec4(Position, 1.0);
    Color = Colors[gl_VertexID];
}