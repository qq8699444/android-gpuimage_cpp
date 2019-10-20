#include <iostream>

using namespace  std;
#include "GPUImageColorMatrixFilter.h"

string GPUImageColorMatrixFilter::COLOR_MATRIX_FRAGMENT_SHADER = "" 
"varying highp vec2 textureCoordinate;\n" 
"\n" 
"uniform sampler2D inputImageTexture;\n" 
"\n" 
"uniform lowp mat4 colorMatrix;\n" 
"uniform lowp float intensity;\n" 
"\n" 
"void main()\n" 
"{\n" 
"    lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
"    lowp vec4 outputColor = textureColor * colorMatrix;\n" 
"    \n" 
"    gl_FragColor = (intensity * outputColor) + ((1.0 - intensity) * textureColor);\n" 
"}";


float GPUImageColorMatrixFilter::mat4I[16] = {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
};

GPUImageColorMatrixFilter::GPUImageColorMatrixFilter(float i, float* mat4) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, COLOR_MATRIX_FRAGMENT_SHADER),
    intensity(i),
    colorMatrix(mat4)
{

}


void GPUImageColorMatrixFilter::onInit() {
    GPUImageFilter::onInit();
    colorMatrixLocation = glGetUniformLocation(getProgram(), "colorMatrix");
    intensityLocation = glGetUniformLocation(getProgram(), "intensity");
}

void GPUImageColorMatrixFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setIntensity(intensity);
    setColorMatrix(colorMatrix);
}

void GPUImageColorMatrixFilter::setIntensity(float i) {
    intensity = i;
    setFloat(intensityLocation, intensity);
}

void GPUImageColorMatrixFilter::setColorMatrix(float* cm) {
    colorMatrix = cm;
    setUniformMatrix4f(colorMatrixLocation, colorMatrix);
}