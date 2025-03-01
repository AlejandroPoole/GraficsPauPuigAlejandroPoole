varying vec2 v_uv;
uniform float u_mode;
uniform float u_task;
uniform float u_time;
uniform sampler2D u_texture;

void main()
{
	if(u_task == 1){
		if (u_mode == 1.0){
			//a)
			vec3 red_color = vec3(v_uv.x,0.0,0.0);
			vec3 blue_color = vec3(0.0,0.0,1.0-v_uv.x);

			vec3 finalColor = blue_color + red_color;
			
			gl_FragColor = vec4(finalColor,1.0);
		}
		else if(u_mode == 2.0){
			//b)
			vec2 center = vec2(0.5,0.5);
			vec2 v = center - v_uv; 
			float leng = length(v);
			vec3 finalColor = vec3(leng,leng,leng);
			
			gl_FragColor = vec4(finalColor,1.0);
		}
		else if(u_mode == 3.0){
			//c)
			vec3 red_color = vec3(sin(50*v_uv.x), 0.0, 0.0);
			vec3 blue_color = vec3(0.0, 0.0, sin(50*v_uv.y));
			vec3 finalColor = red_color + blue_color;
			
			gl_FragColor = vec4(finalColor,1.0);
		}		
		else if(u_mode == 4.0){
			//d)
			vec3 red_color = vec3(v_uv.x - mod(v_uv.x, 0.05), 0, 0);
			vec3 green_color = vec3(0, v_uv.y - mod(v_uv.y, 0.05), 0);
			
			vec3 finalColor = red_color + green_color;

			gl_FragColor = vec4(finalColor,1.0);
		}
		else if (u_mode == 5.0){
			//e)
			vec3 horizontal = vec3(step(sin(50*v_uv.y), 0), step(sin(50*v_uv.y), 0), step(sin(50*v_uv.y), 0));
			vec3 vertical = vec3(step(sin(50*v_uv.x), 0), step(sin(50*v_uv.x), 0), step(sin(50*v_uv.x), 0));

			vec3 finalColor = abs(horizontal - vertical);
			
			gl_FragColor = vec4(finalColor,1.0);
		}
		else if (u_mode == 6.0){

			//f)
			vec3 green_color = vec3(0, abs(v_uv.y - step(0.5 + 0.25*sin(v_uv.x*2*3.14), v_uv.y)), 0);
			
			vec3 finalColor = green_color;

			gl_FragColor = vec4(finalColor,1.0);
		}
	}
	else if(u_task == 2){
		if (u_mode == 1.0){
			//a)
			vec4 texture_color = texture2D(u_texture, v_uv);
			float average = (texture_color.x + texture_color.y + texture_color.z)/3;
			texture_color.x = average;
			texture_color.y = average;
			texture_color.z = average;
			gl_FragColor = texture_color;	
		}
		else if (u_mode == 2.0){
			//b)
			vec4 texture_color = texture2D(u_texture, v_uv);
			texture_color.x = 1-texture_color.x;
			texture_color.y = 1-texture_color.y;
			texture_color.z = 1-texture_color.z;
			gl_FragColor = texture_color;
		}
		else if (u_mode == 3.0){
			//c)
			vec4 texture_color = texture2D(u_texture, v_uv);
			float average = (texture_color.x + texture_color.y)/2;
			texture_color.x = average;
			texture_color.y = average;
			texture_color.z = 0;
			gl_FragColor = texture_color;
		}
		else if (u_mode == 4.0){
			//d)
			vec4 texture_color = texture2D(u_texture, v_uv);
			float average = (texture_color.x + texture_color.y + texture_color.z)/3;
			texture_color.x = step(0.5, sin(average));
			texture_color.y = step(0.5, sin(average));
			texture_color.z = step(0.5, sin(average));
			gl_FragColor = texture_color;
		}
		else if (u_mode == 5.0){
			//e)
			vec4 texture_color = texture2D(u_texture, v_uv);
			vec2 center = vec2(0.5,0.5);
			vec2 v = center - v_uv; 

			texture_color.x *= 0.8 - length(v);
			texture_color.y *= 0.8 - length(v);
			texture_color.z *= 0.8 - length(v);

			gl_FragColor = texture_color;
		}
		else if (u_mode == 6.0){
			//f)
			vec4 texture_color = texture2D(u_texture, v_uv);
			texture_color.x = step(sin(0.5*texture_color.x), 0.2);
			texture_color.y = step(sin(0.5*texture_color.y), 0.2);
			texture_color.z = step(sin(0.5*texture_color.z), 0.2);
			gl_FragColor = texture_color;
		}
	}
	else if (u_task == 3){
		if(u_mode == 1.0){
			vec2 new_uv = vec2(v_uv.y, v_uv.x);
			vec4 texture_color = texture2D(u_texture, new_uv);
			gl_FragColor = texture_color;
		}
		else if(u_mode == 2.0){
			vec2 new_uv = vec2(sin(v_uv.x + u_time/2), v_uv.y);
			vec4 texture_color = texture2D(u_texture, new_uv);
			gl_FragColor = texture_color;
		}
	}
}