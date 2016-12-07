//setup for 2 texture
varying vec2 texcoord0;
varying vec2 texcoord1;

//uniform sampler2DRect tex0;
//uniform vec3 which;
varying float fogAmount;
//uniform vec4 color;
//uniform vec4 color;
varying vec4 colV;

float fog_exp2(
                    const float dist,
                    const float density
                    ) {
    const float LOG2 = -1.442695;
    float d = density * dist;
    return 1.0 - clamp(exp2(d * d * LOG2), 0.0, 1.0);
}

void main(){
//    vec4 color = texture2DRect(tex0, texcoord0);
//    color -= 0.01;
    float fogDistance = gl_FragCoord.z / gl_FragCoord.w;
    float fogAmt = fog_exp2(fogDistance, 0.0005);
//    float f = 1.0 - fogDistance / 10000.0;
//    f = clamp(f, 0.0,1.0);
//    if(gl_Color.r < 0.1){
//        discard;
//    }
    gl_FragColor.rgb = gl_Color.rgb;//mix(gl_Color.rgb, vec3(0.0, 0.0,0.0), fogAmt);//vec4(1.0);//*f;//mix(vec4(1.0,1.0,1.0,0.001), vec4(0.0,0.0,0.0,1.0), fogAmount);//vec4(color.rgb * which, 1.0);
    gl_FragColor.a = 0.003;//mix(0.001, 1.0, fogAmt);// * (f);
    
    
}
