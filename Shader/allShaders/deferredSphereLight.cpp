#include "deferredSphereLight.hpp"
#include <helpful.hpp>
using namespace std;

Shader_deferredSphereLight::Shader_deferredSphereLight()
{
	checkGlError("Start of shader");

	
	const char* vsText = textFileRead("shaders/deferredSphereLight/shader.vert");
	const char* fsText = textFileRead("shaders/deferredSphereLight/shader.frag");
	
	
	string vsource = ShaderManager::getVersion() + "\n";
	string fsource = ShaderManager::getVersion() + "\n";

	vsource += ShaderManager::getGlobalSettingsUniform() + "\n\n";
	vsource += ShaderManager::getViewSettingsUniform() + "\n\n";
	
	fsource += ShaderManager::getDimensionUniform() + "\n\n";
	
	vsource += vsText;
	fsource += fsText;
	
	
	ofstream log;
	getShaderLog(log, "deferredSphereLight");
	
	array<GLuint, 3> out = loadShaders(log,vsource,fsource);
	
	shader_id = out[0];
	shader_vp = out[1];
	shader_fp = out[2];
	
	glBindAttribLocation(shader_id, 0, "in_Vertex");
	glBindFragDataLocation(shader_id, 0, "out_Scene");
	
	
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	
	glUseProgram(shader_id);
	
	GLuint nt = glGetUniformLocation(shader_id, "normalTexture");
	glUniform1i(nt, 0);
	GLuint pt = glGetUniformLocation(shader_id, "posTexture");
	glUniform1i(pt, 1);
	
	uniforms.lightPos = glGetUniformLocation(shader_id, "lightPos");
	
	bindDimensionUniformBlock(shader_id);
	bindGlobalUniformBlock(shader_id);
	bindViewUniformBlock(shader_id);
	
	checkGlError("End of deferredSphereLight");

	
}

