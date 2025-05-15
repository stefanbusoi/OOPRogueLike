#version 330 core

uniform vec2 resolution;
uniform vec2 position;
uniform float time;
uniform sampler2D  tex;
void main()
{

    vec2 uv = (gl_FragCoord.xy)/resolution ;
    vec4 Data = texture(tex, uv);
    uv=uv*resolution;

    vec2 center=resolution/2;
    float d=distance(vec2(uv.x,uv.y),center)/250;
    d=d*d;
    gl_FragColor = vec4(Data.rgb*(clamp(1-d/5,0.3,1)),1);

}