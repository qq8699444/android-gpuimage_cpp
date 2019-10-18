#include <iostream>

using namespace  std;

#include "GPUImageContrastFilter.h"

string GPUImageContrastFilter::CONTRAST_FRAGMENT_SHADER = "" 
        "varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform sampler2D inputImageTexture;\n" 
        " uniform lowp float contrast;\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "     lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "     \n" 
        "     gl_FragColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.w);\n" 
        " }";


GPUImageContrastFilter::GPUImageContrastFilter() :
    GPUImageContrastFilter(1.2f)
{

}


GPUImageContrastFilter::GPUImageContrastFilter(float c):
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, CONTRAST_FRAGMENT_SHADER),
    contrast(c)
{

}

GPUImageContrastFilter::~GPUImageContrastFilter()
{

}

void GPUImageContrastFilter::onInit() {
    GPUImageFilter::onInit();
    contrastLocation = glGetUniformLocation(getProgram(), "contrast");
}

 void GPUImageContrastFilter::onInitialized() {
     GPUImageFilter::onInitialized();
    setContrast(contrast);
}

void GPUImageContrastFilter::setContrast( float contrast) {
    this->contrast = contrast;
    setFloat(contrastLocation, contrast);
}
