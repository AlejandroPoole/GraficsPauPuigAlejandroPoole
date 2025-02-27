varying vec2 v_uv;
uniform float u_mode;
void main()
{	

	v_uv = gl_MultiTexCoord0.xy;

	gl_Position = gl_Vertex;
}