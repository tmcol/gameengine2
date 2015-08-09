uniform sampler2D gTexture;
uniform sampler2D normalTexture;
uniform sampler2D posTexture;

in vec2 pass_ScreenTex;

out vec4 out_Scene;




void main(void)
{	
	vec4 tex = texture(gTexture, pass_ScreenTex);

    out_Scene = vec4(tex.rgb, 1.0);

}
