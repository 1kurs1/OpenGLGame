#shader vertex

#version 450 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ModelViewProjection;

void main()
{
    gl_Position = u_ModelViewProjection * a_Position;
    v_TexCoord = a_TexCoord; 
}

#shader fragment
#version 450 core

layout (location = 0) out vec4 o_color;
in vec2 v_TexCoord;

uniform sampler2D u_texture;

void main()
{
    vec4 texColor = texture(u_texture, v_TexCoord);
	o_color = texColor;
}