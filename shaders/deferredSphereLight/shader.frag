uniform sampler2D normalTexture;
uniform sampler2D posTexture;
uniform vec4 lightPos;


out vec4 out_Scene;


void main(void)
{
	vec2 UV = getScreenUV();
	vec3 normal = texture(normalTexture, UV).xyz;
	vec3 position = texture(posTexture, UV).xyz;
	
	float lightDist = distance(lightPos.xyz, position);
	vec3 lightRay = (lightPos.xyz - position)/lightDist;
	float intensity = max(0, dot(lightRay, normal))*max(0,(lightPos.a-lightDist)/lightPos.a);
	
	out_Scene = vec4(intensity*vec3(1,1,1), 1);
}
