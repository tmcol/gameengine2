#include "helpful.hpp"
#include <Game.hpp>
#include <RenderPipeline.hpp>

std::string intToStr(int a)
{
    std::ostringstream convert;
    convert << a;
    return convert.str();
}

std::string smallIntToStr(int a)
{
    switch(a)
    {
        case 0:
            return "0"; break;
        case 1:
            return "1"; break;
        case 2:
            return "2"; break;
        case 3:
            return "3"; break;
        case 4:
            return "4"; break;
        case 5:
            return "5"; break;
        case 6:
            return "6"; break;
        case 7:
            return "7"; break;
        case 8:
            return "9"; break;
        case 9:
            return "9"; break;
        default:
            return intToStr(a); break;
    }
}

char* textFileRead(const char *fileName)
{
    char* text;
    
    if (fileName != NULL) {
        FILE *file = fopen(fileName, "rt");
        
        if (file != NULL) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);
            
            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';
            }
            fclose(file);
        }
    }
    return text;
}


void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    printf("GL %s = %s\n", name, v);
}

void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        printf("after %s() glError (0x%x)\n", op, error);
    }
}

/*void bindRenderPipelineFramebuffer()
{
    RenderPipeline* rp = dynamic_cast<RenderPipeline*>(Game::getController());
    if(rp!=NULL) glBindFramebuffer(GL_FRAMEBUFFER, rp->getFramebuffer());
    else glBindFramebuffer(GL_FRAMEBUFFER, 0);
}*/
