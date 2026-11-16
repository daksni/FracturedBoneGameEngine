#version 460 core

out vec4 FragColor;

uniform float red;
uniform float green;
uniform float blue;
uniform float alpha;

void main() {
    FragColor = vec4(red, green, blue, alpha);
}