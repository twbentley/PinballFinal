#version 150

in vec4 vPosition;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = worldMatrix * vPosition;
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;
}