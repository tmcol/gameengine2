#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Matrix
{
    GLuint uboFloat;    //UBO for matrix
    GLuint uboPixel;
    GLuint ubo3D;
    
    GLuint uboView;
    
    GLuint uboLight;
    
    GLuint uboDimension;

    //Projection matrices
    glm::mat4 matFloat;
    glm::mat4 matPixel;
    glm::mat4 mat3D;
    glm::mat4 view;
    
    glm::vec4 lights[4];
    
    
    friend class Game;
    protected:
        void update(float, float);
        void init(float, float);
        void deinit();
        
        
    public:
        void useFloat();
        void usePixel();
        void use3D();
        void useView();
        void useLight();
        
        void set3D(const glm::mat4&);
        void setView(const glm::mat4&);
        void setLight(int, const glm::vec3&);
        void updateLight();
        
        glm::mat4 getView(){return view;}
        
		void setModel(const glm::mat4&);
		void setModel();
    
};


#endif
