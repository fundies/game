#version 300 es
layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 color;

out vec2 texCoords;
out vec4 Color;

uniform vec2 outTextureSize;
uniform mat4 projection;

void main()
{
    Color = color / 255.0;

    texCoords = vertex.zw;
    
    //float ox = ((vertex.x + cameraPos.x) / (outTextureSize.x / 2.0)) - 1.0;
    //float oy = ((-vertex.y - cameraPos.y) / (outTextureSize.y / 2.0)) + 1.0;
    
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
}
