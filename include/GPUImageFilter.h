#ifndef GPU_IMAGE_FILTER
#define GPU_IMAGE_FILTER

#include <string>
#include <iostream>
#include <list>
#include <mutex>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#include "Runnable.h"

class GPUImageFilter
{
public:
    GPUImageFilter(); 
    GPUImageFilter(string vertexShader, string fragmentShader); 
    virtual ~GPUImageFilter();
    void init();
    void ifNeedInit();
    void destroy();
    virtual void onOutputSizeChanged(int width, int height);
    virtual void onDraw(int textureId, const GLfloat* cubeBuffer, const GLfloat* textureBuffer);

    bool isInitialized() {
        return bInitialized;
    }

    int getOutputWidth() {
        return outputWidth;
    }

    int getOutputHeight() {
        return outputHeight;
    }

    int getProgram() {
        return glProgId;
    }

    int getAttribPosition() {
        return glAttribPosition;
    }

    int getAttribTextureCoordinate() {
        return glAttribTextureCoordinate;
    }

    int getUniformTexture() {
        return glUniformTexture;
    }


protected:

    static string NO_FILTER_VERTEX_SHADER;
    static string NO_FILTER_FRAGMENT_SHADER;

    virtual void onInit();
    virtual void onInitialized();
    virtual void onDestroy();
    virtual void onDrawArraysPre();
    void runPendingOnDrawTasks();

    void setInteger(int location, int intValue);
    void setFloat(int location, float floatValue);
    void setFloatVec2(int location, float* arrayValue);
    void setFloatVec3(int location, float* arrayValue);
    void setFloatVec4(int location, float* arrayValue);
    void setFloatArray(int location, float* arrayValue, int len);
    void setPoint(int location, float x, float y);
    void setUniformMatrix3f(int location, float* matrix);
    void setUniformMatrix4f(int location, float* matrix);
    void appendRunOnDraw(IRunnable* r);
private:
    std::mutex  runOnDrawLock;
    std::list<IRunnable*> runOnDraw;

    string vertexShader;
    string fragmentShader;
    int glProgId;
    int glAttribPosition;
    int glUniformTexture;
    int glAttribTextureCoordinate;
    int outputWidth;
    int outputHeight;
    bool bInitialized;
};

#endif
