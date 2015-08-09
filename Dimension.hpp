#ifndef DIMENSION_H
#define DIMENSION_H

class Dimension
{
    static float width;
    static float height;
    static float left;
    static float right;
    
    public:
        static void set(float, float);
        static float getRight();
        static float getLeft();
        static float getWidth();
        static float getHeight();
        
        static int xF2P(float x);
        static int yF2P(float y);
        static int mF2P(float m);
    
};

#endif
