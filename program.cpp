#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <iostream>
#include <controllerlist.hpp>
#include <Game.hpp>
#include <Text.hpp>
#include <Repo.hpp>


int main(int args, char* argv[])
{
    unsigned int a;
    glfwInit();

    
    for(int i=0;i<args;i++)
    {
        if(strcmp(argv[i],"--aa")==0)
        {
            if(strcmp(argv[i+1],"2")==0)glfwWindowHint(GLFW_SAMPLES,2);
            if(strcmp(argv[i+1],"4")==0)glfwWindowHint(GLFW_SAMPLES,4);
            if(strcmp(argv[i+1],"8")==0)glfwWindowHint(GLFW_SAMPLES,8);
            if(strcmp(argv[i+1],"16")==0)glfwWindowHint(GLFW_SAMPLES,16);
        }
    }

    
    glfwWindowHint(GLFW_DEPTH_BITS,16);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
     
    GLFWwindow* window = glfwCreateWindow(1280, 720, "", NULL, NULL);//8,8,8, 0, 24, 0, GLFW_FULLSCREEN);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    
    glfwSetKeyCallback(window, Game::keyCallback);

    
    glewExperimental=GL_TRUE;
    glewInit();
    
    std::cout << "GL context created" << std::endl;
    checkGlError("The usual error");
    


    //glLighti(0, GL_SPOT_EXPONENT, 2);
    
    

    
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_CLAMP);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ShaderManager::init();
    Game::init(window, 1280, 720);
    Text::init();
    
    
    Repo::model.load("sphere", Model("sphere.obj"));
    
    glViewport(0, 0, Dimension::getWidth(), Dimension::getHeight());
    
    
    Game::changeController(new SceneController());


    const GLubyte* s = glGetString(GL_VERSION);
    
    std::cout << s << "OK" << std::endl;
    std::cout.flush();

    
    glfwPollEvents();
    
    
    //cout << "Starting loop" << std::endl;;
    while (true)
    {
        //glfwSwapBuffers(window);
        Game::update();
    }

}
