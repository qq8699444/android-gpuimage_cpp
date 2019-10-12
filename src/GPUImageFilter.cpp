#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImageFilter.h"

string GPUImageFilter::NO_FILTER_VERTEX_SHADER = "" 
            "attribute vec4 position;\n" 
            "attribute vec4 inputTextureCoordinate;\n" 
            " \n" 
            "varying vec2 textureCoordinate;\n" 
            " \n" 
            "void main()\n" 
            "{\n" 
            "    gl_Position = position;\n" 
            "    textureCoordinate = inputTextureCoordinate.xy;\n" 
            "}";

string GPUImageFilter::NO_FILTER_FRAGMENT_SHADER = "" 
            "varying highp vec2 textureCoordinate;\n"
            " \n"
            "uniform sampler2D inputImageTexture;\n"
            " \n"
            "void main()\n"
            "{\n"
            "     gl_FragColor = texture2D(inputImageTexture, textureCoordinate);\n"
            "}";



GPUImageFilter::GPUImageFilter():
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, NO_FILTER_FRAGMENT_SHADER)
{

}

GPUImageFilter::GPUImageFilter(string vertexShader, string fragmentShader)
{
    //runOnDraw = new LinkedList<>();
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;
    bInitialized = false;
}

GPUImageFilter:: ~GPUImageFilter()
{
    destroy();
}

void GPUImageFilter::init() {
    onInit();
    onInitialized();
}

void GPUImageFilter::onInit()
{
    glProgId = ShaderUtil::createProgram(vertexShader, fragmentShader);
    glAttribPosition = glGetAttribLocation(glProgId, "position");
    glUniformTexture = glGetUniformLocation(glProgId, "inputImageTexture");
    glAttribTextureCoordinate = glGetAttribLocation(glProgId, "inputTextureCoordinate");
    bInitialized = true;
}

void GPUImageFilter::onInitialized()
{
}

void GPUImageFilter::ifNeedInit()
{
    if (!bInitialized) init();
}

void GPUImageFilter::destroy()
{
    bInitialized = false;
    glDeleteProgram(glProgId);
    onDestroy();
}


void GPUImageFilter::onDestroy()
{
}

void GPUImageFilter::onOutputSizeChanged(int width, int height)
{
    outputWidth = width;
    outputHeight = height;
}

void GPUImageFilter::onDraw(int textureId, const GLfloat* cubeBuffer, const GLfloat* textureBuffer)
{
    glUseProgram(glProgId);
    runPendingOnDrawTasks();
    if (!bInitialized) {
        return;
    }

    //cubeBuffer.position(0);
    glVertexAttribPointer(glAttribPosition, 2, GL_FLOAT, false, 0, cubeBuffer);
    glEnableVertexAttribArray(glAttribPosition);
    ShaderUtil::checkGlError("postion");

    //textureBuffer.position(0);
    glVertexAttribPointer(glAttribTextureCoordinate, 2, GL_FLOAT, false, 0, textureBuffer);
    glEnableVertexAttribArray(glAttribTextureCoordinate);
    ShaderUtil::checkGlError("texture");
    
    if (textureId != -1) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(glUniformTexture, 0);
        ShaderUtil::checkGlError("texture2");
    }
    onDrawArraysPre();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ShaderUtil::checkGlError("glDrawArrays");


    glDisableVertexAttribArray(glAttribPosition);
    glDisableVertexAttribArray(glAttribTextureCoordinate);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GPUImageFilter::onDrawArraysPre()
{

}

void GPUImageFilter::runPendingOnDrawTasks()
{
    //synchronized(runOnDraw) {
    //    while (!runOnDraw.isEmpty()) {
    //        runOnDraw.removeFirst().run();
    //    }
    //}
}

