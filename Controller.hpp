class Controller
{    
    public:
        Controller(){}
        virtual void begin(){}
        virtual void update(){}
        
        virtual void mouse(int, int){}
        virtual void keyboard(int, int){std::cout << "No keyboard handler" << std::endl;}
};
