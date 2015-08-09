#include "SwitchShader.hpp"
#include <fstream>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <helpful.hpp>

#define LOG_CODE

std::array<GLuint, 3> loadShaders(std::ofstream& log, std::string& v, std::string& f)
{
	
	
	GLuint shader_vp = glCreateShader(GL_VERTEX_SHADER);
	GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char* vsource = v.c_str();
	const char* fsource = f.c_str();
	

	
	glShaderSource(shader_vp, 1, &vsource, 0);
	glShaderSource(shader_fp, 1, &fsource, 0);

	glCompileShader(shader_vp);
	glCompileShader(shader_fp);
	
	const unsigned int BUFFER_SIZE = 8192;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;
    
  
    glGetShaderInfoLog(shader_vp, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
		log << "Vertex:" << std::endl;
		log << buffer << std::endl;
    }
    
    glGetShaderInfoLog(shader_fp, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
		log << "Fragment:" << std::endl;
		log << buffer << std::endl;
    }
    
    
    #ifdef LOG_CODE
    log << "\n\nVertex Shader:\n\n" << v << std::endl;
    log << "\n\nFragment Shader:\n\n" << f << std::endl;
    #endif
	
	GLuint shader_id = glCreateProgram();
	
	std::array<GLuint, 3> out;
	out[0]=shader_id;
	out[1]=shader_vp;
	out[2]=shader_fp;
	
	return out;
	
}

void getShaderLog(std::ofstream& log, std::string name)
{
	char fname [64];
	strcpy(fname,"logs/");
	strcat(fname,name.c_str());
	
	std::cout << fname << std::endl;
	
	log.open (fname, std::ios::out | std::ios::trunc);
	
}

void bindDimensionUniformBlock(GLuint shader_id)
{
	GLuint globalIndex = glGetUniformBlockIndex(shader_id, "Dimension");
	glUniformBlockBinding(shader_id, globalIndex, UB_DimensionBinding);
	checkGlError("Binding Dimension");
}

void bindGlobalUniformBlock(GLuint shader_id)
{
	GLuint globalIndex = glGetUniformBlockIndex(shader_id, "GlobalSettings");
	glUniformBlockBinding(shader_id, globalIndex, UB_MatrixBinding);
	checkGlError("Binding Global Block");
}

void bindViewUniformBlock(GLuint shader_id)
{
	GLuint globalIndex = glGetUniformBlockIndex(shader_id, "ViewSettings");
	glUniformBlockBinding(shader_id, globalIndex, UB_ViewBinding);
	checkGlError("Binding View Block");
}

void bindLightUniformBlock(GLuint shader_id)
{
	GLuint globalIndex = glGetUniformBlockIndex(shader_id, "LightSettings");
	glUniformBlockBinding(shader_id, globalIndex,UB_LightBinding);
	checkGlError("Binding Light Block");
}

