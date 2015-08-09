#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <array>
#include <vector>



class Texture
{
    GLuint textureID;
    bool inited = false;
    
    public:
        Texture(GLenum type, std::string fname);
        Texture(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> >);
        Texture(GLenum type, std::string fname, bool fail);
        Texture(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> >, bool fail);
        Texture(const Texture&) = delete;
        Texture& operator = (const Texture&) = delete;
        Texture(Texture&&);
        Texture& operator = (Texture&&);
        
        void init(GLenum type, std::string fname);
        void init(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> >);
        
        void initFail(GLenum type, std::string fname);
        void initFail(GLenum type, std::string fname, std::vector<std::array<GLenum, 2> >);
        
        ~Texture();
        
        GLuint operator * ()
        {
            return textureID;
        }
        
        bool getInit()
        {
            return inited;
        }
        
};

#endif
