#Shader Vertex
#version 330 core
layout(Location = 0) in vec3 position;
layout(Location = 1) in vec3 vertColor;
layout(Location = 2) in vec3 normal;
uniform mat4 MVP;
uniform mat4 ModelToWorldMat;
out vec3 Color;
out vec3 Normal;
out vec3 Position;
void main()
{
   gl_Position = MVP * vec4(position,1.0);
   Color = vertColor;
   Normal = normal;
   Position = vec3(ModelToWorldMat * vec4(position,1.0));
};

#Shader Fragment
#version 330 core
layout(Location = 0) out vec4 color;
uniform vec3 LightLocation;
in vec3 Color;
in vec3 Normal;
in vec3 Position;
void main()
{
    float Brightness = dot(normalize(LightLocation - Position) , Normal);
    color = vec4(Brightness,Brightness,Brightness,1.0f) ;
    //color = vec4(Color * Brightness,1.0f)  ;
};