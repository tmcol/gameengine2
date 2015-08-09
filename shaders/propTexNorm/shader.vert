in vec3 in_Vertex;
in vec2 in_UV;
in vec3 in_Normal;


out vec2 pass_UV;
out vec3 pass_Vertex;
out vec3 pass_Normal;


void main(void)
{
	vec4 vertex = vec4(in_Vertex, 1.0);
	vec4 cameraSpace = viewMatrix * vertex;
	gl_Position = matrix * cameraSpace;
	pass_Vertex = cameraSpace.xyz;
	
	pass_UV = in_UV;
	
	vec4 pass_Normal4 = viewMatrix * vec4(in_Normal, 0.0);
	pass_Normal = pass_Normal4.xyz;

}
