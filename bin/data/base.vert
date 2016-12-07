#define FOG_START 100
#define FOG_END 500

varying vec2 texcoord0;
varying vec2 texcoord1;
varying float fogAmount;
uniform vec2 fog;

attribute vec4 color;

varying vec4 colV;

float fog_linear(const float dist, const float start, const float end ) {
    return 1.0 - clamp((end - dist) / (end - start), 0.0, 1.0);
}

void main()
{
    colV = color;
    // perform standard transform on vertex
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;// ftransform();
    gl_FrontColor = gl_Color;
    // transform texcoords
    texcoord0 = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	texcoord1 = vec2(gl_TextureMatrix[1] * gl_MultiTexCoord0);
   
    float fogDistance = length(gl_Position.xyz);
    fogAmount = fog_linear(fogDistance, fog.x, fog.y);
//    col = gl_Color;
}
