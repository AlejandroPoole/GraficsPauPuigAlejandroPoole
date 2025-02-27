// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec3 v_world_position;
uniform float u_mode;
void main()
{
	// Set the ouput color per pixel
	vec3 color = normalize(v_world_normal);

	gl_FragColor = vec4(1.0*v_world_position,0.0, 1.0 );
}
