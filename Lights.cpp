#include "Lights.hpp"
#include <Repo.hpp>
#include <Game.hpp>

LightSphere::LightSphere(glm::vec3 pos, float s)
{
	position = pos;
	scale = s;
	modelMatrix = glm::scale(glm::translate(glm::mat4(1.f), position), glm::vec3(scale, scale, scale));
}

void LightSphere::render(GLuint loc)
{
	Game::matrix().setModel(modelMatrix);
	
	glm::vec4 lightEye = Game::matrix().getView() * glm::vec4(position, 1.f);
	glUniform4f(loc, lightEye.x, lightEye.y, lightEye.z, scale);	
}

LightStore::LightStore():
	sphere(Repo::model.get("sphere"))
{
}

void LightStore::addLight(LightSphere l)
{
	lights.push_back(l);
}

void LightStore::render()
{
	GLuint lightPos = ShaderManager::getBoundUniform<Shader_deferredSphereLight>().lightPos;
	
	
	glBindVertexArray(sphere.getVAO());
	
	for(LightSphere& ls: lights){
		ls.render(lightPos);
		glDrawArrays(GL_TRIANGLES, 0, sphere.getTriCount()*3);
	}


}
