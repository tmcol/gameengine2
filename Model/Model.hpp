#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <GL/glew.h>

//The buffers which the model contains (virtex buffer is impled)
enum class ModelType
{
	UV,
	NORM
};

class Model
{
	bool valid = false;
	
	GLuint vao;
	GLuint vbo[4];
	
	int buffers;	//Number of VBOs
	int modelType;
	int tris;
	
	void free();
	void moveAssign(Model&&);
	
	public:
	Model(std::string);
	Model(const Model&) = delete;
	Model& operator = (const Model&) = delete;
	Model(Model&&);
	Model& operator = (Model&&);
	~Model();
	
	int getModelType(){
		return modelType;
	}
	
	GLuint getVAO()
	{
		return vao;
	}
	
	int getTriCount()
	{
		return tris;
	}
};

#endif
