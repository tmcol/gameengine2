uniform sampler2D colourTexture;
in vec2 pass_UV;

out vec4 out_Scene;




void main(void)
{	
	vec4 tex = texture(colourTexture, pass_UV);
	
	
	
    
    out_Scene = tex;

}
