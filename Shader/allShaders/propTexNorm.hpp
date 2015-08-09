#include "../SwitchShader.hpp"
#include <string>


//Deferred shading for props
class Shader_propTexNorm: public SwitchShader
{
	
	struct Uniform
	{
		GLuint depthComparison;
	}uniforms;

	
	public:
		Shader_propTexNorm();
		const Uniform& getUniforms() const {return uniforms;}
		
		

	
};


