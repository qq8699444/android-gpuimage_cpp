#include <iostream>

using namespace  std;

#include "GPUImageLevelsFilter.h"

string GPUImageLevelsFilter::LEVELS_FRAGMET_SHADER =
        " varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform sampler2D inputImageTexture;\n" 
        " uniform mediump vec3 levelMinimum;\n" 
        " uniform mediump vec3 levelMiddle;\n"
        " uniform mediump vec3 levelMaximum;\n" 
        " uniform mediump vec3 minOutput;\n" 
        " uniform mediump vec3 maxOutput;\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "     mediump vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "     \n" 
        "     gl_FragColor = vec4( mix(minOutput, maxOutput, pow(min(max(textureColor.rgb -levelMinimum, vec3(0.0)) / (levelMaximum - levelMinimum  ), vec3(1.0)), 1.0 /levelMiddle)) , textureColor.a);\n" 
        " }\n";

GPUImageLevelsFilter::GPUImageLevelsFilter(float min /* = 0.0f */, float mid /* = 1.0f */, float max /* = 1.0f */, float minOUt/* =0.0f */, float maxOut/* =1.0f */) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, LEVELS_FRAGMET_SHADER)
{
    for (int i = 0;i < 3;i++)
    {
        this->min[i] = min;
        this->mid[i] = mid;
        this->max[i] = max;
        this->minOutput[i] = minOUt;
        this->maxOutput[i] = maxOut;
    }
}

void GPUImageLevelsFilter::onInit() {
    GPUImageFilter::onInit();
    minLocation = glGetUniformLocation(getProgram(), "levelMinimum");
    midLocation = glGetUniformLocation(getProgram(), "levelMiddle");
    maxLocation = glGetUniformLocation(getProgram(), "levelMaximum");
    minOutputLocation = glGetUniformLocation(getProgram(), "minOutput");
    maxOutputLocation = glGetUniformLocation(getProgram(), "maxOutput");
}

void GPUImageLevelsFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setMin(0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
    updateUniforms();
}

void GPUImageLevelsFilter::updateUniforms()
{
    setFloatVec3(minLocation, min);
    setFloatVec3(midLocation, mid);
    setFloatVec3(maxLocation, max);
    setFloatVec3(minOutputLocation, minOutput);
    setFloatVec3(maxOutputLocation, maxOutput);
}

void GPUImageLevelsFilter::setMin(float min, float mid, float max, float minOut /* = 0.0f */, float maxOut /* = 1.0f */)
{
    setRedMin(min, mid, max, minOut, maxOut);
    setGreenMin(min, mid, max, minOut, maxOut);
    setBlueMin(min, mid, max, minOut, maxOut);
}

void GPUImageLevelsFilter::setRedMin(float min, float mid, float max, float minOut /* = 0.0f */, float maxOut /* = 1.0f */)
{
    this->min[0] = min;
    this->mid[0] = mid;
    this->max[0] = max;
    minOutput[0] = minOut;
    maxOutput[0] = maxOut;
    updateUniforms();
}

void GPUImageLevelsFilter::setGreenMin(float min, float mid, float max, float minOut, float maxOut )
{
    this->min[1] = min;
    this->mid[1] = mid;
    this->max[1] = max;
    minOutput[1] = minOut;
    maxOutput[1] = maxOut;
    updateUniforms();
}


void GPUImageLevelsFilter::setBlueMin(float min, float mid, float max, float minOut , float maxOut )
{
    this->min[2] = min;
    this->mid[2] = mid;
    this->max[2] = max;
    minOutput[2] = minOut;
    maxOutput[2] = maxOut;
    updateUniforms();
}