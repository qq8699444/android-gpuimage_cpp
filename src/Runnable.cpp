#include <iostream>

using namespace  std;
#include "Runnable.h"
#include "ShaderUtil.h"

Runnable1i::Runnable1i(int location, int intValue)
{
    this->location = location;
    this->intValue = intValue;
}

void Runnable1i::run()
{
    glUniform1i(location, intValue);
    ShaderUtil::checkGlError("Runnable1i");
}

Runnable1f::Runnable1f(int location, float floatValue)
{
    this->location = location;
    this->floatValue = floatValue;
}

void Runnable1f::run()
{
    glUniform1f(location, floatValue);
    ShaderUtil::checkGlError("Runnable1f");
}


Runnable2fv::Runnable2fv(int location, float* valueptr)
{
    this->loc = location;
    this->ptr = valueptr;
}

void Runnable2fv::run()
{
    glUniform2fv(loc, 1, ptr);
    ShaderUtil::checkGlError("Runnable2fv");
}


Runnable3fv::Runnable3fv(int location, float* valueptr)
{
    this->loc = location;
    this->ptr = valueptr;
}

void Runnable3fv::run()
{
    glUniform3fv(loc, 1, ptr);
    ShaderUtil::checkGlError("Runnable3fv");
}

Runnable4fv::Runnable4fv(int location, float* valueptr)
{
    this->loc = location;
    this->ptr = valueptr;
}

void Runnable4fv::run()
{
    glUniform4fv(loc, 1, ptr);
    ShaderUtil::checkGlError("Runnable4fv");
}


RunnableXfv::RunnableXfv(int location, float* valueptr, int len)
{
    this->loc = location;
    this->ptr = valueptr;
    this->len = len;
}

void RunnableXfv::run()
{
    glUniform1fv(loc, len, ptr);
    ShaderUtil::checkGlError("RunnableXfv");
}

RunnablePt::RunnablePt(int location, float x, float y)
{
    this->loc = location;
    this->x = x;
    this->y = y;
}

void RunnablePt::run()
{
    float vec2[2];
    vec2[0] = x;
    vec2[1] = y;
    glUniform2fv(loc, 1, vec2);
    ShaderUtil::checkGlError("RunnablePt");
}

RunnableMatrix3f::RunnableMatrix3f(int location, float* matrix)
{
    this->loc = location;
    this->matrix = matrix;
}

void RunnableMatrix3f::run()
{    
    glUniformMatrix3fv(loc, 1, false, matrix);
    ShaderUtil::checkGlError("RunnableMatrix3f");
}

RunnableMatrix4f::RunnableMatrix4f(int location, float* matrix)
{
    this->loc = location;
    this->matrix = matrix;
}

void RunnableMatrix4f::run()
{
    glUniformMatrix4fv(loc, 1, false, matrix);
    ShaderUtil::checkGlError("glUniformMatrix4fv");
}
