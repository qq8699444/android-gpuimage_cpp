#include <iostream>

using namespace  std;

#include "GPUImageLuminanceThresholdFilter.h"

string GPUImageLuminanceThresholdFilter::LUMINANCE_THRESHOLD_FRAGMENT_SHADER = "" 
        "varying highp vec2 textureCoordinate;\n" 
        "\n" 
        "uniform sampler2D inputImageTexture;\n" 
        "uniform highp float threshold;\n" 
        "\n" 
        "const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);\n" 
        "\n" 
        "void main()\n" 
        "{\n" 
        "    highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "    highp float luminance = dot(textureColor.rgb, W);\n" 
        "    highp float thresholdResult = step(threshold, luminance);\n" 
        "    \n" 
        "    gl_FragColor = vec4(vec3(thresholdResult), textureColor.w);\n" 
        "}";

GPUImageLuminanceThresholdFilter::GPUImageLuminanceThresholdFilter(float s /* = 0.5f */) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, LUMINANCE_THRESHOLD_FRAGMENT_SHADER),
    threshold(s)
{

}


void GPUImageLuminanceThresholdFilter::onInit() {
    GPUImageFilter::onInit();
    uniformThresholdLocation = glGetUniformLocation(getProgram(), "threshold");
}

void GPUImageLuminanceThresholdFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setThreshold(threshold);
}

void GPUImageLuminanceThresholdFilter::setThreshold(float t) {
    threshold = t;
    setFloat(uniformThresholdLocation, threshold);
}
