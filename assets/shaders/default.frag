#version 300 es

precision mediump float;

in vec2 texCoords;
in vec4 Color;

uniform sampler2D image;
uniform vec2 textureSize;

out vec4 FragColor;

void main()
{    
    FragColor = Color * texture(image, vec2(texCoords.x / textureSize.x, texCoords.y / textureSize.y));
} 
