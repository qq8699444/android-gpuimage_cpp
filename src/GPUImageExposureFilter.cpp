#include <iostream>

using namespace  std;

#include "GPUImageExposureFilter.h"

string GPUImageExposureFilter::EXPOSURE_FRAGMENT_SHADER = "" 
        " varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform sampler2D inputImageTexture;\n" 
        " uniform highp float exposure;\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "     highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "     \n" 
        "     gl_FragColor = vec4(textureColor.rgb * pow(2.0, exposure), textureColor.w);\n" 
        " } ";

GPUImageExposureFilter::GPUImageExposureFilter() :
    GPUImageExposureFilter(1.0f)
{

}

GPUImageExposureFilter::GPUImageExposureFilter(float e) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, EXPOSURE_FRAGMENT_SHADER),
    exposure(e)
{

}

GPUImageExposureFilter::~GPUImageExposureFilter()
{

}


void GPUImageExposureFilter::onInit() {
    GPUImageFilter::onInit();
    exposureLocation = glGetUniformLocation(getProgram(), "exposure");
}

void GPUImageExposureFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setExposure(exposure);
}

void GPUImageExposureFilter::setExposure(float exposure) {
    this->exposure = exposure;
    setFloat(exposureLocation, exposure);
}