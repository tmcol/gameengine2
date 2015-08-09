#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Handlers.hpp"


void SimpleInputHandler::handleMouseButton(int button, int action)
{
    std::cout << "Click handler" << std::endl;
    //controllerInfo.playerViewport.click();
};

template<class H>
void TemplatedInputHandler<H>::handleMouseButton(int button, int action)
{    
}

template<class H>
void TemplatedInputHandler<H>::handleKeyboardEvent(int key, int action)
{
    h.keyboard(key, action);
}
