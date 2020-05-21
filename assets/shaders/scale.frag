#version 300 es

precision mediump float;

in vec2 texCoords;

uniform sampler2D image;

out vec4 FragColor;

void main()
{    
    FragColor = texture(image, vec2(texCoords.x, texCoords.y));
} 
