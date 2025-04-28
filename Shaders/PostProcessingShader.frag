#version 330 core

uniform vec2 resolution;
uniform vec2 position;
uniform float time;
uniform sampler2D  tex;
void main()
{

    vec2 uv = (gl_FragCoord.xy) / resolution;

    float pixelSize=max(2,-60+100/time);
    vec4 Data = texture(tex, (uv*resolution-mod(uv*resolution,pixelSize)+pixelSize/2)/resolution);
    // float modTime = sin(time * 2) + cos(time * 1.3193);
    // modTime *= 40.0;
    // vec4 DataR = texture(tex, uv);
    // vec4 DataG = texture(tex, uv+vec2(0,0.001) * modTime);
    //vec4 DataB = texture(tex, uv-vec2(0,0.001) * modTime);



    gl_FragColor = vec4(Data.rgb,1);
}