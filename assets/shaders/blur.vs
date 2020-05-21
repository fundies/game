#version 300 es
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 color;

out vec2 texCoords;
out vec4 Color;

uniform vec2 outTextureSize;

void main()
{
    Color = color * 0.00392156862;
	
    texCoords = vertex.zw;
    
    float ox = ((vertex.x * outTextureSize.x) / (outTextureSize.x / 2.0)) - 1.0;
    float oy = ((-vertex.y * outTextureSize.y) / (outTextureSize.y / 2.0)) + 1.0;
    
    gl_Position = vec4(ox, oy, 0.0, 1.0);
}
