#Shader Vertex
#version 330 core
layout(Location = 0) in vec3 position;
layout(Location = 1) in vec3 vertColor;
uniform mat4 MVP;
out vec3 Color;
void main()
{
   gl_Position = MVP * vec4(position,1.0);
   Color = vertColor;
};

#Shader Fragment
#version 330 core
layout(Location = 0) out vec4 color;
in vec3 Color;
void main()
{
    color = vec4(Color,1.0); 
};