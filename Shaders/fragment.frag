#version 330 core

uniform vec2 resolution;
uniform vec2 position;
uniform float time;
void main()
{
    vec2 center=resolution/2/100;
    vec2 ShaderPosition=position/100;

    vec2 uv = gl_FragCoord.xy / resolution;
    uv.y=-uv.y;

    uv *=resolution;
    uv /= 100;

    vec3 color=mod(floor(uv.x+ShaderPosition.x)+floor(uv.y+ShaderPosition.y),2)==0?vec3(0.4,0.4,0.4):vec3(0.2,0.2,0.2);
    float d=distance(vec2(uv.x,-uv.y),center);


    float modTime = abs(cos(time));

    gl_FragColor=vec4(color,1);
}