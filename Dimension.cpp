#include "Dimension.hpp"
#include <iostream>

void Dimension::set(float w, float h)
{
    float r = w/h;
    left = -r;
    right = r;
    width = w;
    height = h;
    
}

float Dimension::getWidth()
{
    return width;
}
float Dimension::getHeight()
{
    return height;
}
float Dimension::getLeft()
{
    return left;
}
float Dimension::getRight()
{
    return right;
}

int Dimension::xF2P(float x)
{
    return height * x * 0.5 + width/2;
}

int Dimension::yF2P(float y)
{
    return height * (y+1) * 0.5;
}

int Dimension::mF2P(float x)
{
    return height * x * 0.5;
}

float Dimension::width;
float Dimension::height;
float Dimension::left;
float Dimension::right;
