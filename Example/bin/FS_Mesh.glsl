uniform mediump sampler2D Diffuse;

varying highp vec3 vecTransformed;
varying highp vec2 vecUVCoords;

void main()
{
	highp vec3 vector = texture2D(Diffuse,vecUVCoords).rgb;
	gl_FragColor = vec4(vector,1.0);
}
