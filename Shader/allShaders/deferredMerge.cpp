#include "deferredMerge.hpp"
#include <helpful.hpp>
using namespace std;

Shader_deferredMerge::Shader_deferredMerge()
{
	checkGlError("Start of shader");

	
	const char* vsText = textFileRead("shaders/deferredMerge/shader.vert");
	const char* fsText = textFileRead("shaders/deferredMerge/shader.frag");
	
	
	string vsource = ShaderManager::getVersion() + "\n";
	string fsource = ShaderManager::getVersion() + "\n";

	
	
	vsource += vsText;
	fsource += fsText;
	
	
	ofstream log;
	getShaderLog(log, "deferredMerge");
	
	array<GLuint, 3> out = loadShaders(log,vsource,fsource);
	
	shader_id = out[0];
	shader_vp = out[1];
	shader_fp = out[2];
	
	glBindAttribLocation(shader_id, 0, "in_Vertex");
	glBindAttribLocation(shader_id, 1, "in_UV");
	glBindFragDataLocation(shader_id, 0, "out_Scene");
	
	
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	
	glUseProgram(shader_id);
	
	
	GLuint gt = glGetUniformLocation(shader_id, "gTexture");
	glUniform1i(gt, 0);
	GLuint nt = glGetUniformLocation(shader_id, "normalTexture");
	glUniform1i(nt, 1);
	GLuint pt = glGetUniformLocation(shader_id, "posTexture");
	glUniform1i(pt, 2);
	
	checkGlError("End of deferredMerge");

	
}

