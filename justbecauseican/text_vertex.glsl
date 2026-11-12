#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec2 screenSize;

out vec2 TexCoord;

void main()
{
    vec2 normalizedPosition = vec2(
        (aPos.x / screenSize.x) * 2.0 - 1.0,
        1.0 - (aPos.y / screenSize.y) * 2.0
    );

    gl_Position = vec4(normalizedPosition, 0.0, 1.0);

    TexCoord = aTexCoord;
}