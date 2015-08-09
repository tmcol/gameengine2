#ifndef REPO_H
#define REPO_H

#include <map>
#include <string>
#include <Texture.hpp>

template<typename Value>
class ManagerContainer
{
    std::map<std::string, Value> tex;
    
    public:
        void ManagerContainer::load(std::string s, Value&& t)
		{
				tex.insert(std::make_pair(s, std::move(t)));
		}

		Value& ManagerContainer::get(std::string s)
		{
			auto found = tex.find(s);
			if(found == tex.end()){
				assert(false);
			}
			
			return found->second;
		}

		void ManagerContainer::bind(std::string s)
		{
			glBindTexture(GL_TEXTURE_2D, *get(s));
		}
};

class Repo
{
	public:
	static ManagerContainer<Texture> texture;
};


#endif
