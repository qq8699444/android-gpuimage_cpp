#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImageTwoInputFilter.h"

string GPUImageTwoInputFilter::VERTEX_SHADER = "attribute vec4 position;\n" 
            "attribute vec4 inputTextureCoordinate;\n" 
            "attribute vec4 inputTextureCoordinate2;\n" 
            " \n" 
            "varying vec2 textureCoordinate;\n" 
            "varying vec2 textureCoordinate2;\n" 
            " \n" 
            "void main()\n" 
            "{\n" 
            "    gl_Position = position;\n" 
            "    textureCoordinate = inputTextureCoordinate.xy;\n" 
            "    textureCoordinate2 = inputTextureCoordinate2.xy;\n" 
            "}";


GPUImageTwoInputFilter::GPUImageTwoInputFilter(string& fragmentShader):
    GPUImageTwoInputFilter(VERTEX_SHADER, fragmentShader)
{

}

GPUImageTwoInputFilter::GPUImageTwoInputFilter(string& vertexShader, string& fragmentShader):
    GPUImageFilter(vertexShader, fragmentShader),

    filterSourceTexture2(-1)
{
    setRotation(NORMAL, false, false);
}

GPUImageTwoInputFilter::~GPUImageTwoInputFilter()
{

}


void GPUImageTwoInputFilter::onInit()
{
    GPUImageFilter::onInit();

    filterSecondTextureCoordinateAttribute = glGetAttribLocation(getProgram(), "inputTextureCoordinate2");
    checkGLError("glGetAttribLocation inputTextureCoordinate2");

    filterInputTextureUniform2 = glGetUniformLocation(getProgram(), "inputImageTexture2"); // This does assume a name of "inputImageTexture2" for second input texture in the fragment shader
    checkGLError("glGetUniformLocation inputImageTexture2");

    glEnableVertexAttribArray(filterSecondTextureCoordinateAttribute);
    checkGLError("glEnableVertexAttribArray filterSecondTextureCoordinateAttribute");
}

void GPUImageTwoInputFilter::onInitialized()
{
    GPUImageFilter::onInitialized();
    if (!bitmap.empty())
    {
        setBitmap(bitmap);
    }
}

void GPUImageTwoInputFilter::setBitmap(string& bitmap)
{
    this->bitmap = bitmap;


}

void GPUImageTwoInputFilter::onDestroy()
{
    GPUImageFilter::onDestroy();
    glDeleteTextures(1, &filterSourceTexture2);
    filterSourceTexture2 = -1;
}

void GPUImageTwoInputFilter::onDrawArraysPre()
{
    glEnableVertexAttribArray(filterSecondTextureCoordinateAttribute);
    checkGLError("glEnableVertexAttribArray filterSecondTextureCoordinateAttribute");

    glActiveTexture(GL_TEXTURE3);
    checkGLError("glActiveTexture GL_TEXTURE3");

    glBindTexture(GL_TEXTURE_2D, filterSourceTexture2);
    checkGLError("glBindTexture filterSourceTexture2");

    glUniform1i(filterInputTextureUniform2, 3);
    checkGLError("glUniform1i filterInputTextureUniform2");

    //texture2CoordinatesBuffer.position(0);
    glVertexAttribPointer(filterSecondTextureCoordinateAttribute, 2, GL_FLOAT, false, 0, texture2CoordinatesBuffer);
}
void GPUImageTwoInputFilter::setRotation(Rotation rotation, bool flipHorizontal, bool flipVertical)
{
    texture2CoordinatesBuffer = TextureRotationUtil::getRotation(rotation, flipHorizontal, flipVertical);
}