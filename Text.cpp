#include "Text.hpp"
#include <Game.hpp>
#include <Dimension.hpp>

void Text::init()
{
    stash = sth_create(512,512);
    
    addFont(Font::Arial, "Arial.ttf");
    
}

void Text::addFont(Font name, std::string fname)
{
    int font = sth_add_font(stash, fname.c_str());
    db[name] = font;
}


void Text::setShader()
{
    shader = static_cast<Shader_blitAlpha const*>(ShaderManager::getShader(SH_blitAlpha));
    colourLoc = shader->getUniforms().colour;
}

void Text::setColour(float r, float g, float b)
{
    ShaderManager::bind(SH_blitAlpha);
    glUniform4f(colourLoc, r, g, b, 1.f);
}

void Text::beginDraw()
{
    ShaderManager::bind(SH_blitAlpha);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Game::matrix().usePixel();
    sth_begin_draw(stash);
}

void Text::endDraw()
{
    sth_end_draw(stash);
}

void Text::dimensionFloat(Font f, float size,
                  const char* s,
                  float* minx, float* miny, float* maxx, float* maxy)
{
    float h = Dimension::getHeight();
    float w = Dimension::getWidth();
    
    size = 0.5*size*h;
    
    float ix, iy, ax, ay;
    sth_dim_text(stash, db[f], size, s, &ix, &iy, &ax, &ay);
    
    *minx = (2*ix/h);
    *miny = (2*iy/h);
    *maxx = (2*ax/h);
    *maxy = (2*ay/h);
}

void Text::vmetricsFloat(Font f, float size, float* ascender, float* descender, float * lineh)
{
    float h = Dimension::getHeight();
    float w = Dimension::getWidth();
    
    size = 0.5*size*h;
    
    float as, ds, ln;
    sth_vmetrics(stash, db[f], size, &as, &ds, &ln);
    
    *ascender = (2*as/h);
    *descender = (2*ds/h);
    *lineh = (2*ln/h);
}

void Text::vmetricsF2P(Font f, float size, float* ascender, float* descender, float * lineh)
{
    float h = Dimension::getHeight();
    float w = Dimension::getWidth();
    
    size = 0.5*size*h;
    
    sth_vmetrics(stash, db[f], size, ascender, descender, lineh);
}

void Text::drawFloat(Font f, float size, float x, float y, const char* string, float* dx)
{
    float h = Dimension::getHeight();
    float w = Dimension::getWidth();
    //std::cout << 0.5*size*h << " " << 0.5*(x+1)*h << " " << 0.5*(y+1)*h << std::endl;
    sth_draw_text(stash, db[f], 0.5*size*h, 0.5*(w+x*h), 0.5*(y+1)*h, string, dx);
}




Shader_blitAlpha const* Text::shader;
GLuint Text::colourLoc;

sth_stash* Text::stash;

std::map<Font, int> Text::db;

