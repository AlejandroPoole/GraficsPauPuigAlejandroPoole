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




void main()
{	

    float d = distance(u_position, v_world_position);
	vec3 I = (u_intensity/ (d*d));
	//Creating L and N
	vec3 L = u_position  - v_world_position;
	L = normalize(L);
	vec3 N = normalize(v_world_normal);
    //Creating V and R
	vec3 V = u_eye - v_world_position;
	V = normalize(V);
	vec3 R = reflect(-L,N);

	float LN = dot(L,N);
	float RV = dot(R,V);

	vec3 Ia = u_ka*u_Ia;
	vec3 Id = I*(clamp(LN,0.0,1.0)*u_kd);
	vec3 Is = I*(u_ks*pow(clamp(RV,0.0,1.0),u_shininess));
	vec3 Ip = Ia + Id + Is;
	// Project the vertex using the model view projection matrix
    gl_FragColor = vec4(Ip,1.0);
	
}