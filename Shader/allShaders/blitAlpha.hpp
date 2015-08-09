#include "../SwitchShader.hpp"
#include <string>


class Shader_blitAlpha: public SwitchShader
{
	
	GLuint vao;
	GLuint vbo[2];

	friend class ShaderManager;
	struct Uniform
	{
		GLuint colour;
		GLuint projectionMatrix;
	}uniforms;
	
	public:
		Shader_blitAlpha();
		
		GLuint getVAO() const {return vao;}
	
		const Uniform& getUniforms() const {return uniforms;}
		
		

	
};


