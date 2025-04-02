#version 330 core

uniform vec2 resolution;
uniform vec2 position;
uniform float time;
void main()
{
    vec2 center=resolution/2/100;
    vec2 ShaderPosition=position/100;

    vec2 uv = gl_FragCoord.xy / vec2(1920, 1080);

    //uv = vec2(pow(uv.x-.5,cos(time)),pow(uv.y-.5,sin(time))) ;

    //uv += vec2(0, 1) * uv * uv * sin(time * 2);
    //uv += vec2(1, 0) * uv * uv * cos(time * 2.1381);

    //uv = sqrt(sqrt(abs(uv))) * uv;


   // gl_FragColor = vec4(uv, 0, 1);


    uv *= vec2(1920, 1080);
    uv /= 100;

//    return;


    vec3 color=mod(floor(uv.x+ShaderPosition.x)+floor(uv.y+ShaderPosition.y),2)==0?vec3(0.4,0.4,0.4):vec3(0.2,0.2,0.2);
    float d=distance(uv,center);

    float modTime = abs(cos(time));


    gl_FragColor = vec4(color*(clamp(1-d/5,0.3,1)),1);
}