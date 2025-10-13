#version 330 core	     // Minimal GL version support expected from the GPU

uniform vec3 camPos;
uniform vec3 sunPos;
in vec3 fPosition;
in vec3 fNormal;
in vec3 coords;
out vec4 color;	  // Shader output: the color response attached to this fragment


void main() {
	vec3 n = normalize(fNormal);
	vec3 l = normalize(vec3(1.0,1.0,0.5));
	// color = vec4(normalize(fNormal),1.0); // build an RGBA from an RGB
	vec3 v = normalize(camPos);
	vec3 r = 2*n-l;
	vec3 h = normalize(l+v);
	vec3 ambient = vec3(1.0,1.0,1.0)*0;
	vec3 diffuse = max(0,dot(n,l))*fPosition*vec3(1.0,1.0,0.0);// replace last vec by light*surface color
	vec3 specular = max(0,dot(n,h))*fPosition;// replace last vec by light*surface color
	color = vec4(ambient+diffuse+specular,1.0);
	//colorE = vec4(ambient+diffuse+specular,1.0);
}
