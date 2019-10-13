#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImageRGBFilter.h"

string GPUImageRGBFilter::RGB_FRAGMENT_SHADER = "" 
            "  varying highp vec2 textureCoordinate;\n" 
            "  \n" 
            "  uniform sampler2D inputImageTexture;\n" 
            "  uniform highp float red;\n" 
            "  uniform highp float green;\n" 
            "  uniform highp float blue;\n" 
            "  \n" 
            "  void main()\n" 
            "  {\n" 
            "      highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
            "      \n" 
            "      gl_FragColor = vec4(textureColor.r * red, textureColor.g * green, textureColor.b * blue, 1.0);\n" 
            "  }\n";


GPUImageRGBFilter::GPUImageRGBFilter() :
    GPUImageRGBFilter(1.0f, 1.0f, 1.0f)
{

}


GPUImageRGBFilter::GPUImageRGBFilter(float r, float g, float b):
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, RGB_FRAGMENT_SHADER),
    red(r),
    green(g),
    blue(b)
{

}

GPUImageRGBFilter::~GPUImageRGBFilter()
{

}

void GPUImageRGBFilter::onInit()
{
    GPUImageFilter::onInit();
    redLocation = glGetUniformLocation(getProgram(), "red");
    greenLocation = glGetUniformLocation(getProgram(), "green");
    blueLocation = glGetUniformLocation(getProgram(), "blue");
}

void GPUImageRGBFilter::onInitialized()
{
    GPUImageFilter::onInitialized();
    setRed(red);
    setGreen(green);
    setBlue(blue);
}
