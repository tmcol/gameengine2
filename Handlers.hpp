#ifndef HANDLERS_H
#define HANDLERS_H
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>




class Controller;

class InputHandler
{
    
    public:
        virtual void handleMouseButton(int button, int action){exit(0);}
        virtual void handleKeyboardEvent(int key, int action){exit(0);}
        
        virtual ~InputHandler(){}

};

class SimpleInputHandler: public InputHandler
{
    Controller& controller;
    public:
        SimpleInputHandler(Controller& ci):controller(ci){}
        virtual void handleMouseButton(int button, int action);
        virtual void handleKeyboardEvent(int key, int action){};

};

template<class H>
class TemplatedInputHandler: public InputHandler
{
    H& h;
    public:
        TemplatedInputHandler(H& _h):h(_h){}
        virtual void handleMouseButton(int button, int action);
        virtual void handleKeyboardEvent(int key, int action);

};

#endif
