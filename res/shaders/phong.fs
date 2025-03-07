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
uniform float u_colorTexture;
uniform float u_specularTexture;
uniform float u_normalTexture;
uniform sampler2D u_textureNorm;
// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;




void main()
{	
	vec3 Ip = vec3(0);
	// Project the vertex using the model view projection matrix
vec4 texture_color = texture2D(u_texture, v_uv);
	if(u_colorTexture == 0.00 && u_normalTexture == 0.00 && u_specularTexture == 0.00){
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
	Ip = Ia + Id + Is;
	 
	}
	else if(u_colorTexture == 1.00){
	

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

	vec3 Ia = texture_color.xyz*u_Ia;
	vec3 Id = I*(clamp(LN,0.0,1.0)*texture_color.xyz);
	vec3 Is = I*(u_ks*pow(clamp(RV,0.0,1.0),u_shininess));
	Ip = Ia + Id + Is;

	
	}
	else if(u_specularTexture == 1.00){


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

	vec3 Ia = texture_color.xyz*u_Ia;
	vec3 Id = I*(clamp(LN,0.0,1.0)*texture_color.xyz);
	vec3 Is = I*(texture_color.a*pow(clamp(RV,0.0,1.0),u_shininess));
	 Ip = Ia + Id + Is;
	}
	else if(u_normalTexture == 1.00){
		
	vec4 texture_c = texture2D(u_textureNorm, v_uv);
	
	vec3 N_position = (u_model * vec4(texture_c.xyz, 1.0)).xyz;

	float d = distance(u_position, v_world_position);
	vec3 I = (u_intensity/ (d*d));
	//Creating L and N
	vec3 L = u_position  - v_world_position;
	L = normalize(L);
	vec3 N = normalize(N_position);
	N = N*2 -vec3(1);
    //Creating V and R
	vec3 V = u_eye - v_world_position;
	V = normalize(V);
	vec3 R = reflect(-L,N);

	float LN = dot(L,N);
	float RV = dot(R,V);

	vec3 Ia = texture_color.xyz*u_Ia;
	vec3 Id = I*(clamp(LN,0.0,1.0)*texture_color.xyz);
	vec3 Is = I*(texture_color.a*pow(clamp(RV,0.0,1.0),u_shininess));
	Ip = Ia + Id + Is;
	}
	


gl_FragColor = vec4(Ip,1.0);
   
	
}