#include <stdlib.h>
#include <GL/glew.h>
#include <unistd.h>
#include <controllerlist.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <helpful.hpp>
#include <Game.hpp>
#include <Text.hpp>
#include <Repo.hpp>
#include <chrono>

SceneController::SceneController()
{

    
    
    GLuint b;
    
    
    //globalInfo.setInputHandler(new SimpleInputHandler(*this));
    inputMapper.setMapping(85, BeatA);
    inputMapper.setMapping(73, BeatB);
    inputMapper.setMapping(79, BeatC);
    inputMapper.setMapping(80, BeatD);
    inputMapper.setMapping(74, HoldA);
    inputMapper.setMapping(75, HoldB);
    inputMapper.setMapping(76, HoldC);
    inputMapper.setMapping(59, HoldD);
    inputMapper.resetGroups();
    
    
    //noteStream.load("sea_ex.ksh");
    
    
    /*a = glGetError();
    if (a!=0)cout << "C0" << a << std::endl;*/
    
    
    glClearColor(0.0,0.0,0.0,1);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);
    
    time_t start = time(0);
    struct tm * now = localtime( & start );
    start_time=now->tm_sec;
    
    //cout << start_time << std::endl;
    //exit(0);
    count=0;
 
    
    ShaderManager::bind(SH_blitAlpha);
    GLuint projectionLoc = ShaderManager::getBoundUniform<Shader_blitAlpha>().projectionMatrix;
    
    glm::mat4 ortho = glm::ortho(0.f, 1368.f, 0.f, 768.f, 1.f, -1.f);
    
    glUniformMatrix4fv(projectionLoc, 1, false, &ortho[0][0]);
    
    
    glm::mat4 p3d = glm::perspective(1.2f, 16.0f/9.0f, 0.5f, 14.0f);
    Game::matrix().set3D(p3d);
    
    
    glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -3.f, 0.f)) * glm::rotate(glm::mat4(1.0f), 0.6f, glm::vec3(1.f,0.f,0.f)) * glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -2.5f));
    Game::matrix().setView(view);
    Game::matrix().useView();
    

    Game::matrix().setLight(0, glm::vec3(0.f, 2.5f, -2.f));
    Game::matrix().setLight(1, glm::vec3(0.f, 2.5f, -5.5f));
    Game::matrix().setLight(2, glm::vec3(0.f, 2.5f, -9.f));
    Game::matrix().updateLight();
    Game::matrix().useLight();
        
	
	float s = 5.f;
	glm::mat4 modelMatrix = glm::scale(glm::translate(glm::mat4(1.f), glm::vec3(0.f, -5.f, -1.5f)), glm::vec3(s,s,s));
	
	Repo::texture.load("crit", Texture(GL_RGB, "critical.png"));
    Repo::model.load("bunny", Model("uvbunny.obj"));
        
    
    propStore.addProp(Prop("bunny", "crit", modelMatrix));
    propStore.addProp(Prop("bunny", "crit", glm::rotate(glm::translate(glm::mat4(1.f), glm::vec3(1.5f, 1.f, -3.5f)), -1.f, glm::vec3(0.f, 1.f, 0.f))));
    propStore.addProp(Prop("bunny", "crit", glm::rotate(glm::translate(glm::mat4(1.f), glm::vec3(-1.5f, 1.f, -3.5f)), 1.f, glm::vec3(0.f, 1.f, 0.f))));
    
    for(int j=0; j<2; j++)
		for(int i=0; i<5; i++)
			lightStore.addLight(LightSphere(glm::vec3(-4.f + i*2, 0.5f+j*2, -2.f), 2));
    
    //lightStore.addLight(LightSphere(glm::vec3(-2.f, 2.f, -1.f), 5));
}

void SceneController::update()
{
	checkGlError("Frame start");
    
    
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    framestart = glfwGetTime();

    glViewport( 0, 0, Dimension::getWidth(), Dimension::getHeight());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    
    checkGlError("Clear buffers");
    
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_CLAMP);
    
    renderPipeline.prepare();
    
    Game::matrix().use3D();
    
    propStore.render();
    
    
    //renderPipeline.fx();
    renderPipeline.lighting();
    
    lightStore.render();
    
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glDisable(GL_DEPTH_TEST);
   
    Text::beginDraw();
    Text::draw(Font::Arial, 24.0f, 10, 10, "Hello");
    Text::endDraw();
    
    glViewport(0,0,Dimension::getWidth(),Dimension::getHeight());

   
    checkGlError("Finished draw calls");
    
   
    
    Game::flip();
    
    
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    float interval = glfwGetTime() - framestart;

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	

	std::cout << "@ " << 1/time_span.count() << " / " << 1/interval << " fps." << std::endl;

    double delay = 1/interval;
    
    if(delay<min)min=delay;
    if(delay>max)max=delay;
    
    rolling[countMode]+=delay;
    if(frames >= 60)
    {
        frames=0;
        countMode=!countMode;
        rolling[countMode] = 0.f;
    }
    else frames++;
    
    fpsAvg = (rolling[0] + rolling[1])/(frames+60);
    
    //cout << delay << "\n";//min << " " << max << " " << avg << std::endl;
    
    double continuetime = framestart+1.0/60.0;

    
    while (glfwGetTime() < continuetime){
        usleep(1000);
    }

    glfwPollEvents();
    
    
    checkGlError("pollevents");
    //exit(0);
    
    //cout << 1/(glfwGetTime() - framestart);
}


void SceneController::keyboard(int key, int action)
{
    if(action == 2)return;
    std::cout << "Key " << key << " action " << action << std::endl;
    inputMapper.input(key, action);
}
