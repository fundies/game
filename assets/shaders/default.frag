#version 300 es
#define FIX(c) max(abs(c), 1e-5);

precision highp float;

in vec2 texCoords;
in vec4 Color;

uniform sampler2D image;
uniform vec2 textureSize;

out vec4 FragColor;

const float PI = 3.1415926535897932384626433832795;

vec4 weight4(float x)
{
    const float radius = 2.0;
    vec4 sampl = FIX(PI * vec4(1.0 + x, x, 1.0 - x, 2.0 - x));

    // Lanczos2. Note: we normalize below, so no point in multiplying by radius.
    vec4 ret = /*radius **/ sin(sampl) * sin(sampl / radius) / (sampl * sampl);

    // Normalize
    return ret / dot(ret, vec4(1.0));
}

vec4 pixel(float xpos, float ypos)
{
    return texture2D(image, vec2(xpos, ypos));
}

vec4 line(float ypos, vec4 xpos, vec4 linetaps)
{
    return mat4x4(
        pixel(xpos.x, ypos),
        pixel(xpos.y, ypos),
        pixel(xpos.z, ypos),
        pixel(xpos.w, ypos)) * linetaps;
}

void main()
{
    vec2 stepxy = 1.0 / textureSize.xy;
    vec2 pos = texCoords.xy / textureSize.xy + stepxy * 0.5;
    vec2 f = fract(pos / stepxy);

    vec2 xystart = (-1.5 - f) * stepxy + pos;
    vec4 xpos = vec4(
        xystart.x,
        xystart.x + stepxy.x,
        xystart.x + stepxy.x * 2.0,
        xystart.x + stepxy.x * 3.0);

    vec4 linetaps   = weight4(f.x);
    vec4 columntaps = weight4(f.y);

    FragColor = mat4x4(
        line(xystart.y                 , xpos, linetaps),
        line(xystart.y + stepxy.y      , xpos, linetaps),
        line(xystart.y + stepxy.y * 2.0, xpos, linetaps),
        line(xystart.y + stepxy.y * 3.0, xpos, linetaps)) * columntaps;

    FragColor *= Color;
}
