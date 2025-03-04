// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec3 v_world_position;
varying vec2 v_uv;
varying vec3 Ip;
uniform sampler2D u_texture;

uniform float u_shininess;
uniform vec3 u_kd;
uniform vec3 u_ks;
uniform vec3 u_ka;

void main()
{
	// Set the ouput color per pixel
	vec4 texture_color = texture2D(u_texture, v_uv);
	// vec3 color = normalize(v_world_normal);

	gl_FragColor = texture_color;
}