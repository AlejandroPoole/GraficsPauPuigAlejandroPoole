
// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex

varying vec2 v_uv;
varying vec3 Ip;


uniform mat4 u_model;
uniform mat4 u_viewprojection;
//here create uniforms for all the data we need here
uniform vec3 u_kd;
uniform vec3 u_ks;
uniform vec3 u_ka;
uniform sampler2D u_texture;
uniform float u_shininess;
uniform vec3 u_Ia;
uniform vec3 u_intensity;
uniform vec3 u_position;
uniform vec3 u_eye;


void main()
{
	// Set the ouput color per pixel
	
	// vec3 color = normalize(v_world_normal);
	
	gl_FragColor = vec4(Ip,1.0);
}