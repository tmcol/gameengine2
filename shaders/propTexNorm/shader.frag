uniform sampler2D colourTexture;

in vec2 pass_UV;
in vec3 pass_Vertex;
in vec3 pass_Normal;

out vec4 out_Scene;
out vec3 out_Normal;
out vec3 out_Position;



void main(void)
{	
	vec4 tex = texture(colourTexture, pass_UV);
	out_Scene = vec4(tex.rgb, 1.0);
	
	out_Normal = normalize(pass_Normal);
	out_Position = pass_Vertex;
}
