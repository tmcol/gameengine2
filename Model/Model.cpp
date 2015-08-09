#include "Model.hpp"
#include <Character/modelLoader.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <helpful.hpp>

Model::Model(std::string mname)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
	loadOBJ(mname.c_str(), vertices, uvs, normals);
	
	
	tris = vertices.size()/3;
	
	buffers=1;
	if(uvs.size())buffers+=1;
	if(normals.size())buffers+=1;
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(buffers, vbo);
	
	glBindVertexArray(vao);
	
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat) * 3, vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    modelType = 0;
    int bufIdx = 1;
    
    if(uvs.size()){
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[bufIdx]);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat) * 2, uvs.data(), GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		bufIdx++;
		modelType |= enum2mask(ModelType::UV);
	}
	
	if(normals.size()){
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[bufIdx]);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat) * 3, normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		bufIdx++;
		modelType |= enum2mask(ModelType::NORM);
	}
	
	valid = true;
}

void Model::moveAssign(Model&& m)
{
	assert(m.valid);
	
	m.valid = false;
	valid = true;
	vao = m.vao;
	std::copy(m.vbo, m.vbo+m.buffers, vbo);
	
	modelType = m.modelType;
	buffers = m.buffers;
	tris = m.tris;
}

Model::Model(Model&& m)
{
	moveAssign(std::move(m));
}

Model& Model::operator= (Model&& m)
{
	free();
	moveAssign(std::move(m));
}

void Model::free()
{
	if(!valid) return;
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(buffers, vbo);
}

Model::~Model()
{
	free();
}
