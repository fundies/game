#version 300 es
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 color;

out vec2 texCoords;
out vec4 Color;

uniform vec2 outTextureSize;
uniform mat4 projection;
uniform vec2 textureSize;

float r(float N, float L) {
 return (0.5/L)+(N/L);
}

void main()
{
    Color = color / 255.0;

    texCoords = vertex.zw;
    
    gl_Position = projection * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
