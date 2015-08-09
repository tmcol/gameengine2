in vec3 in_Vertex;


void main(void)
{
	vec4 vertex = vec4(in_Vertex, 1.0);
	vec4 cameraSpace = viewMatrix * vertex;
	gl_Position = matrix * cameraSpace;
	
	

}
