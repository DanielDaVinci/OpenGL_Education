#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    if (ourColor == vec3(0.0, 0.0, 0.0))
        color = texture(ourTexture, TexCoord);
    else
        color = vec4(ourColor, 1.0);
}