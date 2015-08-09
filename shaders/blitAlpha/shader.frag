uniform vec4 colour = vec4(1.f, 1.f, 1.f, 1.f);

uniform sampler2D colourTexture;

in vec2 pass_UV;

out vec4 out_Scene;


void main(void)
{

	float a = texture(colourTexture, pass_UV).r;
	
	out_Scene = vec4(colour.rgb, a * colour.a);
	//out_Scene = vec4(1,1,1,a);
}
