#version 120

attribute vec3 position;
attribute vec2 textureCoord;

varying vec2 textureCoord0;

uniform mat4 trans;


void main()
{
	gl_Position = trans*vec4(position, 1.0);
	textureCoord0 = textureCoord;
	
}
