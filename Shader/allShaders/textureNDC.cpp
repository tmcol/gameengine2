#include "textureNDC.hpp"
#include <helpful.hpp>
using namespace std;

Shader_textureNDC::Shader_textureNDC()
{
	unsigned int a;
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error3: " << a << endl;
	
	const string block =
"";

	
	const char* vsText = textFileRead("shaders/textureNDC/shader.vert");
	const char* fsText = textFileRead("shaders/textureNDC/shader.frag");
	
	
	string vsource = ShaderManager::getVersion() + "\n";
	string fsource = ShaderManager::getVersion() + "\n";

	
	vsource += block + "\n\n";
	fsource += block + "\n\n";
	
	vsource += vsText;
	fsource += fsText;
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error2: " << a << endl;

	cout << "blitTexture gregmvmwmwemjiomioweiocropcjopqweopr\n\n\n\n" << endl;
	cout << vsource << endl;
	cout << "blitTexture pregmvmwmwemjiomioweiocropcjopqweopr\n\n\n\n" << endl;
	cout << fsource << endl;
	cout << "blitTexture gregmvmwmwemjiomioweiocropcjopqweopr\n\n\n\n" << endl;
	
	ofstream log;
	getShaderLog(log, "textureNDC");
	
	array<GLuint, 3> out = loadShaders(log,vsource,fsource);
	
	shader_id = out[0];
	shader_vp = out[1];
	shader_fp = out[2];
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error12: " << a << endl;
	glBindAttribLocation(shader_id, 0, "in_Vertex");
	glBindAttribLocation(shader_id, 1, "in_UV");
	glBindFragDataLocation(shader_id, 0, "out_Scene");
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error111: " << a << endl;
	
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	
	char buffer[512];
	memset(buffer, 0, 512);
	GLsizei length = 0;
	glGetProgramInfoLog(shader_id, 512, &length, buffer);
	if (length > 0) {
		log << "Program:" << endl;
		log << buffer << endl;
	}
	
	glUseProgram(shader_id);
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error11: " << a << endl;
	GLuint ct = glGetUniformLocation(shader_id, "colourTexture");
	
	
	glUniform1i(ct, 0);
	

	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error1: " << a << endl;

	
}

