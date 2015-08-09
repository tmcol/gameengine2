in vec2 in_Vertex;
in vec2 in_UV;


out vec2 pass_ScreenTex;

void main(void)
{
	gl_Position = vec4(in_Vertex, 0.0, 1.0);
	pass_ScreenTex = (gl_Position.xy / gl_Position.w)*0.5 + vec2(0.5, 0.5);

}
