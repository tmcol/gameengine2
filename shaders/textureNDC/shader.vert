in vec2 in_Vertex;
in vec2 in_UV;

out vec2 pass_UV;

void main(void)
{
	gl_Position = vec4(in_Vertex, 0.0, 1.0);
	pass_UV = in_UV;

}
