#include "../SwitchShader.hpp"
#include <string>


class Shader_deferredSphereLight: public SwitchShader
{
	friend class ShaderManager;
	struct Uniform{
		GLuint lightPos;
	}uniforms;
	
	public:
		Shader_deferredSphereLight();
	
		

	
};


