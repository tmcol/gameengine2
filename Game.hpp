#ifndef GAME_H
#define GAME_H

#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "controllerlist.hpp"
#include "Matrix.hpp"

class Game
{
    Game();
    
    static Controller* controller;
    static Controller* newController;
    
    //static std::array<int, 2> size;    //Window size
    static GLFWwindow* window;
    static Matrix _matrix;
    
    public:
        static void init(GLFWwindow*, float, float);
        static void update();
        static void changeController(Controller*);
        static void flip();
        
        template<class T>
        static T& getController(){
            T* c = dynamic_cast<T*>(controller);
            if(c==NULL)
                assert(false);
            return *c;
        }
        
        static Controller* getController(){
            return controller;
        }
        
        static Matrix& matrix(){return _matrix;}
        /*
        static float getHeight(){return size[1];}
        static float getWidth(){return size[0];}
        */
        
        static void mouseClickCallback(GLFWwindow* w, int b, int a, int modifiers);
        static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
        
        
};


#endif
