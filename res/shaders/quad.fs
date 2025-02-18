varying vec2 v_uv;

void main()
{
	
	vec3 red_color = vec3(v_uv.x,0.0,0.0);
	vec3 blue_color = vec3(0.0,0.0,1.0-v_uv.x);

	vec3 finalColor = blue_color + red_color;
	
	gl_FragColor = vec4(finalColor,1.0);
}
