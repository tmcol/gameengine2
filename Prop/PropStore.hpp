#ifndef PROPSTORE_H
#define PROPSTORE_H

#include <Prop/Prop.hpp>
#include <vector>

class PropStore
{
	std::vector<Prop> opaque;
	
	public:
		void addProp(Prop&&);
		
		void render();
};

#endif
