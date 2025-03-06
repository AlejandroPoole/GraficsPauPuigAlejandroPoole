// Global variables from the CPU
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
// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 Ip;



void main()
{	
	v_uv = gl_MultiTexCoord0.xy;
	// Convert local position to world space
	vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;

	// Convert local normal to world space
	vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz;

	// Pass them to the fragment shader interpolated
	v_world_position = world_position;
	v_world_normal = world_normal;

	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader

	float d = distance(v_world_position, u_position);

	//Creating L and N
	vec3 L = u_position  - v_world_position;
	L = normalize(L);
	vec3 N = v_world_normal;
    //Creating V and R
	vec3 V = u_eye - v_world_position;
	V = normalize(V);
	vec3 R = reflect(-L,N);

	Ip = (u_ka*u_Ia) + (u_intensity/ pow(d,2))*((clamp(dot(L,N),0,1)*u_kd) + (u_ks*pow(clamp(dot(R,V),0,1),u_shininess)));
	// Project the vertex using the model view projection matrix
	
	
}