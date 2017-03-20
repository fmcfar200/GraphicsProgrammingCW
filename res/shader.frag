#version 120

varying vec2 textureCoord0;
uniform sampler2D diff;


void main()
{
	gl_FragColor = texture2D(diff,textureCoord0);
}


