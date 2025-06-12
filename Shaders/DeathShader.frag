#version 330 core

uniform vec2 resolution;
uniform vec2 position;
uniform float time;
uniform sampler2D  tex;
void main()
{

    vec2 uv = (gl_FragCoord.xy)/resolution ;

    float datar=texture(tex,uv+vec2(0.01f,0.0f)).b;
    float datag=texture(tex,uv+vec2(0.01f,0.01f)).r;
    float datab=texture(tex,uv+vec2(0.0f,0.01f)).g;
    uv=uv*resolution;

    vec2 center=resolution/2;


    gl_FragColor = vec4(datar,datag,datab,1);

}