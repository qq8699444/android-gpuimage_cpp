#include <iostream>

using namespace  std;

#include "GPUImageFalseColorFilter.h"

string GPUImageFalseColorFilter::FALSECOLOR_FRAGMENT_SHADER = "" 
        "precision lowp float;\n" 
        "\n" 
        "varying highp vec2 textureCoordinate;\n" 
        "\n" 
        "uniform sampler2D inputImageTexture;\n" 
        "uniform float intensity;\n" 
        "uniform vec3 firstColor;\n" 
        "uniform vec3 secondColor;\n" 
        "\n" 
        "const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n" 
        "\n" 
        "void main()\n" 
        "{\n" 
        "lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "float luminance = dot(textureColor.rgb, luminanceWeighting);\n" 
        "\n" 
        "gl_FragColor = vec4( mix(firstColor.rgb, secondColor.rgb, luminance), textureColor.a);\n" 
        "}\n";

GPUImageFalseColorFilter::GPUImageFalseColorFilter(float firstRed /* = 0.0f */, float firstGreen /* = 0.0f */, float firstBlue /* = 0.5f */, 
                float secondRed /* = 1.f */, float secondGreen /* = 0.0f */, float secondBlue /* = 0.0f */):
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, FALSECOLOR_FRAGMENT_SHADER)
{
    firstColor[0] = firstRed;
    firstColor[1] = firstGreen;
    firstColor[2] = firstBlue;

    secondColor[0] = secondRed;
    secondColor[1] = secondGreen;
    secondColor[2] = secondBlue;
}

void GPUImageFalseColorFilter::onInit() {
    GPUImageFilter::onInit();
    firstColorLocation = glGetUniformLocation(getProgram(), "firstColor");
    secondColorLocation = glGetUniformLocation(getProgram(), "secondColor");
}

void GPUImageFalseColorFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setFirstColor(firstColor);
    setSecondColor(secondColor);
}

void GPUImageFalseColorFilter::setFirstColor(float* fc) {
    memcpy(firstColor, fc,sizeof(firstColor));
    setFloatVec3(firstColorLocation, firstColor);
}

void GPUImageFalseColorFilter::setSecondColor(float* sc) {
    memcpy(secondColor, sc, sizeof(secondColor));
    setFloatVec3(secondColorLocation, secondColor);
}