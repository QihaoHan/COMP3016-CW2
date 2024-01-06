#version 410 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	FragColor =  mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x, 1.0 - TexCoord.y)), 0.3);
}