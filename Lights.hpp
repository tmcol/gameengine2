#ifndef LIGHTS_H
#define LIGHTS_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Model/Model.hpp>

class LightSphere
{
	
	
	glm::vec3 position;
	float scale;
	
	glm::mat4 modelMatrix;
	
	public:
		LightSphere(glm::vec3, float);
		void render(GLuint);
		
};

class LightStore
{
	Model& sphere;
	
	std::vector<LightSphere> lights;
	
	public:
		LightStore();
		void addLight(LightSphere);
		void render();

};

#endif
