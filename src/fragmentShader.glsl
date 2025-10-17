#version 330 core	     // Minimal GL version support expected from the GPU

uniform vec3 camPos;
uniform vec3 sunPos;
uniform vec3 col;
uniform vec3 lighting;
uniform vec3 lcolor;
in vec3 fPosition;
in vec3 fNormal;
in vec3 coords;
out vec4 color;	  // Shader output: the color response attached to this fragment


void main() {
	vec3 n = normalize(fNormal);
	// color = vec4(normalize(fNormal),1.0); // build an RGBA from an RGB
	vec3 v = normalize(camPos);
	vec3 r = 2*n-lighting;
	vec3 h = normalize(lighting+v);
	vec3 ambient = col/3;
	vec3 diffuse = 0*max(0,dot(n,lighting))*lcolor*col/10;// replace last vec by light*surface color
	vec3 specular = max(0,dot(n,h))*lcolor*col;// replace last vec by light*surface color
	color = vec4(ambient+diffuse+specular,1.0);
	//colorE = vec4(diffuse+specular,1.0);
}
