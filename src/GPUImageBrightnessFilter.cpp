#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImageBrightnessFilter.h"


string GPUImageBrightnessFilter::BRIGHTNESS_FRAGMENT_SHADER = "" 
        "varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform sampler2D inputImageTexture;\n" 
        " uniform lowp float brightness;\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "     lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "     \n" 
        "     gl_FragColor = vec4((textureColor.rgb + vec3(brightness)), textureColor.w);\n" 
        " }";

GPUImageBrightnessFilter::GPUImageBrightnessFilter() :
    GPUImageBrightnessFilter(0.0f)
{

}

GPUImageBrightnessFilter::GPUImageBrightnessFilter(float b):
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, BRIGHTNESS_FRAGMENT_SHADER),
    brightness(b)
{

}

GPUImageBrightnessFilter::~GPUImageBrightnessFilter()
{

}

void GPUImageBrightnessFilter::onInit() {
    GPUImageFilter::onInit();
    brightnessLocation = glGetUniformLocation(getProgram(), "brightness");
}

void GPUImageBrightnessFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setBrightness(brightness);
}

void GPUImageBrightnessFilter::setBrightness(float b) {
    this->brightness = b;
    setFloat(brightnessLocation, this->brightness);
}