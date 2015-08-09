#define STB_IMAGE_IMPLEMENTATION

#include <png++/png.hpp>
#include <stb_image.h>
#include "Texture.hpp"
#include <images/imageLoad.hpp>


Texture::Texture(GLenum type, std::string fname)
{
    init(type, fname, {});
}

Texture::Texture(GLenum type, std::string fname, bool fail)
{
    if(fail == false)init(type, fname, {});
    else initFail(type, fname, {});
}

Texture::Texture(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> > params)
{
    init(type, fname, params);
}

Texture::Texture(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> > params, bool fail)
{
    if(fail == false)init(type, fname, params);
    else initFail(type, fname, params);
}

void Texture::init(GLenum type, std::string fname)
{
    init(type, fname, {});
}

void Texture::initFail(GLenum type, std::string fname)
{
    initFail(type, fname, {});
}

void Texture::init(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> > params)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    
    for(int i=0; i<params.size(); i++)
    {
        glTexParameteri(GL_TEXTURE_2D, params[i][0], params[i][1]);
    }
    
    std::cout << "Init " << fname;
    
    try
    {
        png::image<png::rgba_pixel> image (fname);
        GLubyte* imgdata =  extractData(image, false, false);
        
        glTexImage2D(GL_TEXTURE_2D, 0, type, image.get_width(), image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imgdata);
        
        delete imgdata;
        
        std::cout << " - success" << std::endl;
        
    }
    catch(png::std_error& e)
    {
        unsigned char white[16] = {255,0,255,255,0,0,0,0,0,255,255,255,0,0,0,0};
        glTexImage2D(GL_TEXTURE_2D, 0, type, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
        
        std::cout << " - fail" << std::endl;
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    inited = true;
}

void Texture::initFail(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> > params)
{
    std::cout << "InitFail " << fname;
    
    try
    {
        FILE *file = fopen(fname.c_str(), "rb");
        
        if (!file)
            return ;

        int width, height, comp;
        unsigned char* imgdata = stbi_load_from_file(file, &width, &height, &comp, 0);
        fclose(file);
    
    
        //png::image<png::rgba_pixel> image (fname);
        //GLubyte* imgdata = extractData(image, false, false);
        
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
        
        std::cout << comp << " " << textureID << " " << GL_RGB << " " << type << " " << width << " " << height << std::endl;
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        
        for(int i=0; i<params.size(); i++)
        {
            glTexParameteri(GL_TEXTURE_2D, params[i][0], params[i][1]);
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        stbi_image_free(imgdata);
        
        inited = true;
        
        std::cout << " - success" << std::endl;
        
    }
    catch(png::std_error& e)
    {
        std::cout << " - fail" << std::endl;
    }

    
    
    
    
}

Texture::Texture(Texture&& t)
{
    operator=(std::move(t));
}

Texture& Texture::operator = (Texture&& t)
{
	if(inited)glDeleteTextures(1, &textureID);
	
    textureID = t.textureID;
    inited = t.inited;
    t.inited = false;
}


Texture::~Texture()
{
    if(inited)glDeleteTextures(1, &textureID);
}
