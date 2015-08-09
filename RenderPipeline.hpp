#ifndef RENDERPIPELINE_H
#define RENDERPIPELINE_H

#include <Shader/allShaders/allShaders.hpp>
#include <helpful.hpp>
#include <Dimension.hpp>

class DeferredRenderPipeline
{
    GLuint deferredBuffer;
    GLuint gTexture;
    GLuint normalTexture;
    GLuint posTexture;
    GLuint depthBuffer;
    
    GLuint lightingBuffer;
    GLuint lightingTexture;
    
    GLuint vao;
    GLuint vbo;
    
    public:
    DeferredRenderPipeline();
    
    void prepare();
    void lighting();
    void fx();
    
    float getFramebuffer(){
        return deferredBuffer;
    }
};

#endif
