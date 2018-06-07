#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 normal;
uniform mat4 proj;
uniform mat4 model;

out vec2 v_TexCoord;
out vec3 theColor;

void main()
{
	vec4 p = vec4(position, 1.0);
	vec4 modelp = model * p;
	vec4 projp = proj * modelp;
	gl_Position = projp;
//	gl_Position = vec4(position, 1.0);
	theColor = vertexColor;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 theColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;


void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	//color = texColor; //RGB + alpha
	color = vec4(theColor, 1.0);
};