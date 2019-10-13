#ifndef _RUNABLE_H_
#define _RUNABLE_H_

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif


class IRunnable
{
public:
    virtual ~IRunnable() {};
    virtual void run() = 0;
};

class Runnable1i : public IRunnable
{
public:
    Runnable1i(int location, int intValue);
    virtual void run();
protected:
private:
    int location;
    int intValue;
};

class Runnable1f : public IRunnable
{
public:
    Runnable1f(int location, float floatValue);
    virtual void run();
protected:
private:
    int location;
    float floatValue;
};


class Runnable2fv : public IRunnable
{
public:
    Runnable2fv(int location, float* valueptr);
    virtual void run();
protected:
private:
    int loc;
    float* ptr;
};

class Runnable3fv : public IRunnable
{
public:
    Runnable3fv(int location, float* valueptr);
    virtual void run();
protected:
private:
    int loc;
    float* ptr;
};


class Runnable4fv : public IRunnable
{
public:
    Runnable4fv(int location, float* valueptr);
    virtual void run();
protected:
private:
    int loc;
    float* ptr;
};


class RunnableXfv : public IRunnable
{
public:
    RunnableXfv(int location, float* valueptr,int len);
    virtual void run();
protected:
private:
    int loc;
    float* ptr;
    int len;
};

class RunnablePt : public IRunnable
{
public:
    RunnablePt(int location, float x,float y);
    virtual void run();
protected:
private:
    int loc;
    float x;
    float y;
};


class RunnableMatrix3f : public IRunnable
{
public:
    RunnableMatrix3f(int location, float* matrix);
    virtual void run();
protected:
private:
    int loc;
    float* matrix;
};

class RunnableMatrix4f : public IRunnable
{
public:
    RunnableMatrix4f(int location, float* matrix);
    virtual void run();
protected:
private:
    int loc;
    float* matrix;
};

#endif