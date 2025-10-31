#version 330 core	     // Minimal GL version support expected from the GPU

uniform vec3 camPos;
uniform vec3 sunPos;
uniform vec3 col;
uniform vec3 lighting;
uniform vec3 lcolor;

uniform sampler2D material;

in vec3 fPosition;
in vec3 fNormal;
in vec3 coords;
in vec2 fragmentTexCoord;
out vec4 color;	  // Shader output: the color response attached to this fragment


void main() {
	vec3 n = normalize(fNormal);
	vec3 v = normalize(camPos);
	vec3 l = normalize(lighting);
	l = vec3(l.x,-l.y, l.z);
	vec3 r = 2*n-l;
	vec3 h = normalize(l+v);
	vec3 ambient = col;
	vec3 diffuse = max(0,dot(n,l))*lcolor*col*3;
	vec3 specular = pow(max(0,dot(n,h)), 20.0)*lcolor*col;
	//color = vec4(ambient+diffuse+specular,1.0);
	// color = vec4(diffuse+specular,1.0)+texture(material, fragmentTexCoord);
	color = vec4(ambient+diffuse+specular,1.0)*texture(material, fragmentTexCoord);
	//color = texture(material, fragmentTexCoord);
	//color = vec4(ambient+diffuse+specular,1.0)+texture(material, vec2(clamp(fragmentTexCoord.x,0.01,0.99),fragmentTexCoord.y));
}
