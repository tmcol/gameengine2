#ifndef PROP_H
#define PROP_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Prop
{
	GLuint vao;
	GLuint tris;
	GLuint texture;
	
	glm::mat4 modelMatrix;

	public:
		Prop(std::string, std::string, glm::mat4);
		void render();
};

#endif
