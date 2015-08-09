#include "SwitchShader.hpp"
#include "allShaders/allShaders.hpp"



SwitchShader::~SwitchShader()
{
		//TODO ?
}


void ShaderManager::init()
{
	
	shaders[SH_propTexNorm] = new Shader_propTexNorm;
	shaders[SH_blitAlpha] = new Shader_blitAlpha;
	shaders[SH_deferredMerge] = new Shader_deferredMerge;
	shaders[SH_deferredSphereLight] = new Shader_deferredSphereLight;
	
	glUseProgram(0);
	bound = 0;
	//bind(0);
	
	std::cout << "Set up shaders" << std::endl;
	
	
}


std::string ShaderManager::getVersion()
{
	return "#version 330";
}

std::string ShaderManager::getDimensionUniform()
{
	return "\
layout( std140 ) uniform Dimension {\n\
	vec4 dimension;\n\
};\n\
vec2 getScreenUV(){\n\
	return vec2(gl_FragCoord.x*dimension.x, gl_FragCoord.y*dimension.y);\n\
}\n\
\n\
";
}

std::string ShaderManager::getGlobalSettingsUniform()
{
	return "\
layout( std140 ) uniform GlobalSettings {\n\
	mat4 matrix;\n\
};\n\
\n\
";
}

std::string ShaderManager::getViewSettingsUniform()
{
	return "\
layout( std140 ) uniform ViewSettings {\n\
	mat4 viewMatrix;\n\
};\n\
\n\
";
}

std::string ShaderManager::getLightSettingsUniform()
{

return "\
layout( std140 ) uniform LightSettings {\n\
	vec3 light[3];\n\
};\n\
";
}


std::map<int, SwitchShader*> ShaderManager::shaders;
int ShaderManager::bound;
