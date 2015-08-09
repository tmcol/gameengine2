#ifndef CONTROLLERLIST_H
#define CONTROLLERLIST_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <vector>

#include <RenderPipeline.hpp>
#include <Controller.hpp>
#include <InputMapper.hpp>
#include <Prop/PropStore.hpp>
#include <Lights.hpp>



class SceneController:    public Controller
{
    unsigned int* vbo;
    int count;
    float start_time;
    unsigned int vao;
    int mx,my;
    bool mouseActive;
    
    float min=10000;
    float max=0;
    float rolling[2] = {0.f};
    int frames=0;
    bool countMode=false;
    float interval=1/60.f;
    float fpsAvg;
    double framestart;
   
	PropStore propStore;
    LightStore lightStore;
    
    public:
        
        virtual void keyboard(int, int);
        
        void update();
        SceneController();
        
        GLuint globalUBO;
        GLubyte* globalUBuffer;
        
        GLuint v,u;

        
        InputMapper inputMapper;
        
        DeferredRenderPipeline renderPipeline;
                

        
};

/*
class SongSelectController: public Controller
{
    std::string folderPath;
    void loadSongs();
    
    
    
    int songOffset=0;
    std::vector<SongPanel*> allSongs;
    
    glm::mat4 p3d;
    glm::mat4 portho;
    glm::mat4 viewMatrix;
    
    Rolodex rolodex;
    SongInfo songInfo;
    
    
    public:
    
    SongSelectController();
    
    
    
    virtual void keyboard(int, int);
        
    void update();
    
    
};
*/
#endif
