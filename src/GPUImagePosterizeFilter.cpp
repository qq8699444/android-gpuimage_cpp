#include <iostream>

using namespace  std;
#include "ShaderUtil.h"

#include "GPUImagePosterizeFilter.h"


string GPUImagePosterizeFilter::POSTERIZE_FRAGMENT_SHADER = "" 
        "varying highp vec2 textureCoordinate;\n" 
        "\n" 
        "uniform sampler2D inputImageTexture;\n" 
        "uniform highp float colorLevels;\n" 
        "\n" 
        "void main()\n" 
        "{\n" 
        "   highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "   \n" 
        "   gl_FragColor = floor((textureColor * colorLevels) + vec4(0.5)) / colorLevels;\n" 
        "}";


GPUImagePosterizeFilter::GPUImagePosterizeFilter() :
    GPUImagePosterizeFilter(10)
{

}


GPUImagePosterizeFilter::GPUImagePosterizeFilter(int cl) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, POSTERIZE_FRAGMENT_SHADER),
    colorLevels(cl)
{

}

GPUImagePosterizeFilter::~GPUImagePosterizeFilter()
{

}


void GPUImagePosterizeFilter::onInit()
{
    GPUImageFilter::onInit();
    glUniformColorLevels = glGetUniformLocation(getProgram(), "colorLevels");
    checkGLError("glGetUniformLocation colorLevels");
}


void GPUImagePosterizeFilter::onInitialized()
{
    GPUImageFilter::onInitialized();
    setColorLevels(colorLevels);
}


void GPUImagePosterizeFilter::setColorLevels(int colorLevels)
{
    this->colorLevels = colorLevels;
    setFloat(glUniformColorLevels, 1.0f * colorLevels);
}