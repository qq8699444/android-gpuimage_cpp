#include <iostream>

using namespace  std;

#include "GPUImageSaturationFilter.h"


string GPUImageSaturationFilter::SATURATION_FRAGMENT_SHADER = ""
        " varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform sampler2D inputImageTexture;\n" 
        " uniform lowp float saturation;\n" 
        " \n" 
        " // Values from \"Graphics Shaders: Theory and Practice\" by Bailey and Cunningham\n" 
        " const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "    lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "    lowp float luminance = dot(textureColor.rgb, luminanceWeighting);\n" 
        "    lowp vec3 greyScaleColor = vec3(luminance);\n" 
        "    \n" 
        "    gl_FragColor = vec4(mix(greyScaleColor, textureColor.rgb, saturation), textureColor.w);\n" 
        "     \n" 
        " }";


GPUImageSaturationFilter::GPUImageSaturationFilter() :
    GPUImageSaturationFilter(1.0f)
{

}


GPUImageSaturationFilter::GPUImageSaturationFilter(float s) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, SATURATION_FRAGMENT_SHADER),
    saturation(s)
{

}


GPUImageSaturationFilter::~GPUImageSaturationFilter()
{

}

void GPUImageSaturationFilter::onInit() {
    GPUImageFilter::onInit();
    saturationLocation = glGetUniformLocation(getProgram(), "saturation");
}

void GPUImageSaturationFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setSaturation(saturation);
}

void GPUImageSaturationFilter::setSaturation(float saturation) {
    this->saturation = saturation;
    setFloat(saturationLocation, saturation);
}