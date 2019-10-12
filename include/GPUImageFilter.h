#ifndef GPU_IMAGE_FILTER
#define GPU_IMAGE_FILTER

#include <string>
#include <iostream>
#include <list>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

class GPUImageFilter
{
public:
    GPUImageFilter(); 
    GPUImageFilter(string vertexShader, string fragmentShader); 
    virtual ~GPUImageFilter();
    void init();
    void ifNeedInit();
    void destroy();
    void onOutputSizeChanged(int width, int height);
    void onDraw(int textureId, const GLfloat* cubeBuffer, const GLfloat* textureBuffer);

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
private:
    //private final LinkedList<Runnable> runOnDraw;
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
