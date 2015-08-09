#ifndef TEXT_H
#define TEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fontstash/fontstash.h>
#include <map>


#include <Shader/allShaders/allShaders.hpp>

enum class Font
{
    Arial,
    
    __MAX
};


enum Align
{
    ALIGN_LEFT,
    ALIGN_CENTRE,
    ALIGN_RIGHT
};

class Text
{
    static Shader_blitAlpha const* shader;
    static GLuint colourLoc;

    static sth_stash* stash;
    
    static std::map<Font, int> db;
    
    protected:
        static void addFont(Font, std::string);
        static void setShader();
        
    public:
        
        
        static void init();
        static void beginDraw();
        static void endDraw();
        
        static void setColour(float r, float g, float b);
        
        static void dimension(Font f, float size,
                  const char* s,
                  float* minx, float* miny, float* maxx, float* maxy)
        {
                sth_dim_text(stash, db[f], size, s, minx, miny, maxx, maxy);
        }
        static void dimensionFloat(Font f, float size,
                  const char* s,
                  float* minx, float* miny, float* maxx, float* maxy);
        
        
        static void vmetricsFloat(Font f, float size, float* ascender, float* descender, float * lineh);
        static void vmetricsF2P(Font f, float size, float* ascender, float* descender, float * lineh);
        static void vmetrics(Font f, float size, float* ascender, float* descender, float * lineh)
        {
                sth_vmetrics(stash, db[f], size, ascender, descender, lineh);
        }
        
        
        static void drawFloat(Font f, float size, float x, float y, const char* string, float* dx = NULL);

        static void draw(Font f, float size, float x, float y, const char* string, float* dx = NULL)
        {
                sth_draw_text(stash, db[f], size, x, y, string, dx);
        }
    
};

#endif
