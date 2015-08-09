#include "RenderPipeline.hpp"

void checkFB(const char* message)
{
	switch(glCheckFramebufferStatus(GL_FRAMEBUFFER))
	{

		case GL_FRAMEBUFFER_COMPLETE_EXT:    printf("The fbo is complete\n"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:    printf("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT\n"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:    printf("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT\n"); break;   
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:    printf("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:    printf("GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n"); break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:    printf("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n"); break;
		default:  std::cout << GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT << std::endl; break;
	}
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){std::cout << "FB FAIL! " << message << std::endl;exit(0);}
}
   
DeferredRenderPipeline::DeferredRenderPipeline()
{
	glGenFramebuffers(1, &deferredBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, deferredBuffer);
	
	
	glGenTextures(1, &gTexture);
	glBindTexture(GL_TEXTURE_2D, gTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Dimension::getWidth(), Dimension::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gTexture, 0);
	
	glGenTextures(1, &normalTexture);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Dimension::getWidth(), Dimension::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexture, 0);
	
	glGenTextures(1, &posTexture);
	glBindTexture(GL_TEXTURE_2D, posTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Dimension::getWidth(), Dimension::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, posTexture, 0);
	
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Dimension::getWidth(), Dimension::getHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	
	checkFB("deferred");
	
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	
	
	
	glGenFramebuffers(1, &lightingBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, lightingBuffer);
	
	
	glGenTextures(1, &lightingTexture);
	glBindTexture(GL_TEXTURE_2D, lightingTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Dimension::getWidth(), Dimension::getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lightingTexture, 0);
	
	checkFB("lighting");
	
	GLfloat rect[] = {
		-1.f, -1.f,
		1.f, -1.f,
		1.f, 1.f,
		-1.f, -1.f,
		1.f, 1.f,
		-1.f, 1.f
	};
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(GLfloat) * 6, rect, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	   
}

void DeferredRenderPipeline::prepare()
{
	glBindFramebuffer(GL_FRAMEBUFFER, deferredBuffer);        
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLuint buf[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, buf);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GLuint buf[] = {GL_BACK_LEFT, GL_NONE, GL_NONE};
	glDrawBuffers(3, buf);*/
}

void DeferredRenderPipeline::fx()
{
	checkGlError("fx start");
	
	ShaderManager::bind(SH_deferredMerge);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, posTexture);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	return;
}

#define LIGHTDEBUG

void DeferredRenderPipeline::lighting()
{
	ShaderManager::bind(SH_deferredSphereLight);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, posTexture);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	
	#ifdef LIGHTDEBUG
		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	#else
		glBindFramebuffer(GL_FRAMEBUFFER, lightingBuffer);
		glClear(GL_COLOR_BUFFER_BIT);
	#endif
	

}
