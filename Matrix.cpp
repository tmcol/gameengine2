#include "Matrix.hpp"
#include <Shader/SwitchShader.hpp>

void Matrix::init(float pw, float ph)
{
    glGenBuffers(1, &uboFloat);
    glGenBuffers(1, &uboPixel);
    glGenBuffers(1, &ubo3D);
    glGenBuffers(1, &uboView);
    glGenBuffers(1, &uboLight);
    glGenBuffers(1, &uboDimension);
    
    update(pw, ph);
    useFloat();
}

void Matrix::update(float pw, float ph)
{
    float r = pw/ph;
    
    matFloat = glm::ortho(-r, r, -1.f, 1.f, -1.f, 1.f);
    matPixel = glm::ortho(0.f, pw, 0.f, ph);
    
    glBindBuffer(GL_UNIFORM_BUFFER, uboFloat);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &matFloat, GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_UNIFORM_BUFFER, uboPixel);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &matPixel, GL_DYNAMIC_DRAW);
    
    
    glm::vec4 dim(1.f/pw, 1.f/ph, pw, ph);
    glBindBuffer(GL_UNIFORM_BUFFER, uboDimension);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), &dim, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, UB_DimensionBinding, uboDimension);
}

void Matrix::set3D(const glm::mat4& m)
{
    mat3D = m;
    
    glBindBuffer(GL_UNIFORM_BUFFER, ubo3D);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &mat3D, GL_DYNAMIC_DRAW);
    
}

void Matrix::setView(const glm::mat4& m)
{
    view = m;
}

void Matrix::setModel(const glm::mat4& m)
{
	glm::mat4 mv = view * m;
	glBindBuffer(GL_UNIFORM_BUFFER, uboView);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &mv, GL_DYNAMIC_DRAW);
}

void Matrix::setModel()
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboView);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &view, GL_DYNAMIC_DRAW);
}

void Matrix::setLight(int i, const glm::vec3& l)
{
    lights[i] = glm::vec4(l, 1.0f);
}

void Matrix::useFloat()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, UB_MatrixBinding, uboFloat);
}

void Matrix::usePixel()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, UB_MatrixBinding, uboPixel);
}

void Matrix::use3D()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, UB_MatrixBinding, ubo3D);
}

void Matrix::useView()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, UB_ViewBinding, uboView);
}

void Matrix::updateLight()
{
    glm::vec4 l[4];
    
    for(int i=0; i<3; i++){
        l[i] = view * lights[i];
    }
    
    glBindBuffer(GL_UNIFORM_BUFFER, uboLight);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4)*4, l, GL_DYNAMIC_DRAW);
}

void Matrix::useLight()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, UB_LightBinding, uboLight);
    
}

void Matrix::deinit()
{
    glDeleteBuffers(1, &uboFloat);
    glDeleteBuffers(1, &uboPixel);
    glDeleteBuffers(1, &ubo3D);
    glDeleteBuffers(1, &uboView);
    glDeleteBuffers(1, &uboDimension);
}
