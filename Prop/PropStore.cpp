#include "PropStore.hpp"
#include <Shader/SwitchShader.hpp>

void PropStore::addProp(Prop&& p)
{
	opaque.push_back(std::move(p));	
}

void PropStore::render()
{
	ShaderManager::bind(SH_propTexNorm);
	for(Prop& p: opaque){
		p.render();
	}
}
