#include <InputMapper.hpp>

void InputMapper::input(int k, bool action)
{
    
    if(mappings.count(k)==0)return;
    
    Button b = mappings[k];
    /*
    if(standard)
    {
        noteStream.input(b, action);
        effectInfo.input(b, action);
    }
    else
    {
        for(auto o: groups[b])
        {
            noteStream.input(o, action);
            effectInfo.input(o, action);
        }
    }*/
}

void InputMapper::setGroup(Button b, std::set<Button> s)
{
    groups[b] = s;
}
void InputMapper::setMapping(int key, Button b)
{
    mappings[key] = b;
}

void InputMapper::resetGroups()
{
    standard = true;
}
void InputMapper::resetMappings()
{
    mappings.clear();
}

void InputMapper::resetGroup(Button b)
{
    groups[b] = std::set<Button>({b});
}
void InputMapper::resetMapping(int key)
{
    mappings.erase(key);
}
