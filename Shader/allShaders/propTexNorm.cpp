#include "propTexNorm.hpp"
#include <helpful.hpp>
using namespace std;

Shader_propTexNorm::Shader_propTexNorm()
{
	unsigned int a;
	
	
	const char* vsText = textFileRead("shaders/propTexNorm/shader.vert");
	const char* fsText = textFileRead("shaders/propTexNorm/shader.frag");
	
	
	string vsource = ShaderManager::getVersion() + "\n";
	string fsource = ShaderManager::getVersion() + "\n";
	
	vsource += ShaderManager::getGlobalSettingsUniform() + "\n\n";
	
	vsource += ShaderManager::getViewSettingsUniform() + "\n\n";
	
	vsource += vsText;
	fsource += fsText;
	
	ofstream log;
	getShaderLog(log, "propTexNorm");
	
	array<GLuint, 3> out = loadShaders(log,vsource,fsource);
	
	shader_id = out[0];
	shader_vp = out[1];
	shader_fp = out[2];
	
	glBindAttribLocation(shader_id, 0, "in_Vertex");
	glBindAttribLocation(shader_id, 1, "in_UV");
	glBindFragDataLocation(shader_id, 0, "out_Scene");
	glBindFragDataLocation(shader_id, 1, "out_Normal");
	glBindFragDataLocation(shader_id, 2, "out_Position");
	
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	glUseProgram(shader_id);
	
	GLuint ct = glGetUniformLocation(shader_id, "colourTexture");
	glUniform1i(ct, 0);
	

	bindGlobalUniformBlock(shader_id);
	bindViewUniformBlock(shader_id);
	
	
	checkGlError("Shader error propTexNorm");

	
}

