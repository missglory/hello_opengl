#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 texCoord;
uniform mat4 proj;
uniform mat4 model;
uniform mat4 ortho;
uniform mat4 mvp;

out vec2 v_TexCoord;
out vec3 theColor;
out vec3 positionVec;

void main()
{
	//vec4 p = vec4(position, 1.0);
	//vec4 orth = ortho * p;
	//vec4 translated = model * orth;
	//vec4 newp = proj * translated;
	positionVec = position;
	gl_Position = mvp * vec4(position, 1.0);
	v_TexCoord = texCoord.xy;
	theColor = vertexColor;
};



#shader fragment
#version 330 core

//layout(location = 0) out vec4 color;
out vec4 color;

in vec2 v_TexCoord;
in vec3 theColor;
in vec3 positionVec;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform samplerCube cubeMap;

void main()
{
	//vec4 texColor = texture(cubeMap, positionVec);
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor; //RGB + alpha
	//color = vec4(theColor, 1.0);
};