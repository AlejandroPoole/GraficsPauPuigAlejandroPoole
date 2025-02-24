varying vec2 v_uv;
void main()
{
	//b)
	// vec2 center = vec2(0.5,0.5);
	// vec2 v = center - v_uv; 
	// float leng = length(v);
	// vec3 finalColor = vec3(leng,leng,leng);
	
	// gl_FragColor = vec4(finalColor,1.0);
	
	//a)
	// vec3 red_color = vec3(v_uv.x,0.0,0.0);
	// vec3 blue_color = vec3(0.0,0.0,1.0-v_uv.x);

	// vec3 finalColor = blue_color + red_color;
	
	// gl_FragColor = vec4(finalColor,1.0);

	//c)
	// vec3 red_color = vec3(step(sin(25*v_uv.x), 0.003), 0, 0);
	// vec3 blue_color = vec3(0, 0, step(sin(25*v_uv.y), 0.003));
	// vec3 finalColor = red_color + blue_color;
	
	// gl_FragColor = vec4(finalColor,1.0);	

	//d)
	// vec3 red_color = vec3(v_uv.x - mod(v_uv.x, 0.05), 0, 0);
	// vec3 green_color = vec3(0, v_uv.y - mod(v_uv.y, 0.05), 0);
	
	// vec3 finalColor = red_color + green_color;

	// gl_FragColor = vec4(finalColor,1.0);

	//e)
	// vec3 horizontal = vec3(step(sin(50*v_uv.y), 0), step(sin(50*v_uv.y), 0), step(sin(50*v_uv.y), 0));
	// vec3 vertical = vec3(step(sin(50*v_uv.x), 0), step(sin(50*v_uv.x), 0), step(sin(50*v_uv.x), 0));

	// vec3 finalColor = abs(horizontal - vertical);
	
	// gl_FragColor = vec4(finalColor,1.0);

	//f)
	// vec3 green_color = vec3(0, abs(v_uv.y - step(0.5 + 0.25*sin(v_uv.x*2*3.14), v_uv.y)), 0);
	
	// vec3 finalColor = green_color;

	// gl_FragColor = vec4(finalColor,1.0);
}