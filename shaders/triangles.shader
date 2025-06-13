#shader vertex

#version 450 core
layout(location = 0) in vec3 a_Position;
out vec3 pos;

void main()
{
    pos = a_Position;
    gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 450 core

layout (location = 0) out vec4 o_color;
in vec3 pos;

uniform vec4 u_color;

void main()
{
	o_color = vec4((pos.x)/u_color.x, (pos.y + 0.05)/u_color.y, (pos.z + 0.05)/u_color.z, 1.0);
}