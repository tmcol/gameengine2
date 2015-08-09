#ifndef INPUTMAPPER_H
#define INPUTMAPPER_H

#include <set>
#include <map>

enum Button
{
    HoldA, 
    HoldB, 
    HoldC, 
    HoldD, 
    BeatA,
    BeatB,
    BeatC,
    BeatD,
    LaserLL,
    LaserLR,
    LaserRL,
    LaserRR
};


class InputMapper
{
    std::map<int, Button> mappings;    //Links keys to one of 12 note groups
    
    std::set<Button> groups[12];    //Links each note group to a set of notes
    bool standard; //Use the standard mappings
    
    
    public:
    

    
    void input(int, bool);
    
    void setMapping(int, Button);
    void resetMappings();
    void resetMapping(int);
    
    void setGroup(Button, std::set<Button>);
    void resetGroups();
    void resetGroup(Button);
    
};

#endif
