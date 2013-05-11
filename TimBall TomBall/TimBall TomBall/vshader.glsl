#version 150

in vec4 vPosition;
out vec4 color;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 vColor;

void main()
{
	gl_Position = worldMatrix * vPosition;
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;

	color = vColor;
}