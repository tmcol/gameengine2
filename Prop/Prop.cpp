#include "Prop.hpp"

#include <Repo.hpp>
#include <helpful.hpp>
#include <Game.hpp>

Prop::Prop(std::string a, std::string b, glm::mat4 m):
	modelMatrix(m)
{
	Model& model = Repo::model.get(a);
	int modelType = model.getModelType();
	assert(modelType & enum2mask(ModelType::UV) && enum2mask(ModelType::NORM));
	
	vao = model.getVAO();
	texture = *(Repo::texture.get(b));
	tris = model.getTriCount();
}

void Prop::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	Game::matrix().setModel(modelMatrix);
	
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, tris*3);
}
