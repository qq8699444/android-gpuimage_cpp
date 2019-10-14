#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImagePixelationFilter.h"


string GPUImagePixelationFilter::PIXELATION_FRAGMENT_SHADER = "" 
        "precision highp float;\n" 
        "varying vec2 textureCoordinate;\n" 
        "uniform float imageWidthFactor;\n" 
        "uniform float imageHeightFactor;\n" 
        "uniform sampler2D inputImageTexture;\n" 
        "uniform float pixel;\n" 
        "void main()\n" 
        "{\n" 
        "  vec2 uv  = textureCoordinate.xy;\n" 
        "  float dx = pixel * imageWidthFactor;\n" 
        "  float dy = pixel * imageHeightFactor;\n" 
        "  vec2 coord = vec2(dx * floor(uv.x / dx), dy * floor(uv.y / dy));\n" 
        "  vec3 tc = texture2D(inputImageTexture, coord).xyz;\n" 
        "  gl_FragColor = vec4(tc, 1.0);\n" 
        "}";


GPUImagePixelationFilter::GPUImagePixelationFilter() :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, PIXELATION_FRAGMENT_SHADER),
    pixel(1.0f)
{

}


GPUImagePixelationFilter::~GPUImagePixelationFilter()
{

}


void GPUImagePixelationFilter::onInit()
{
    GPUImageFilter::onInit();
    imageWidthFactorLocation = glGetUniformLocation(getProgram(), "imageWidthFactor");
    imageHeightFactorLocation = glGetUniformLocation(getProgram(), "imageHeightFactor");
    pixelLocation = glGetUniformLocation(getProgram(), "pixel");
}


void GPUImagePixelationFilter::onInitialized()
{
    GPUImageFilter::onInitialized();
    setPixel(pixel);
}


void GPUImagePixelationFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    setFloat(imageWidthFactorLocation, 1.0f / width);
    setFloat(imageHeightFactorLocation, 1.0f / height);
}

void GPUImagePixelationFilter::setPixel(float pixel)
{
    this->pixel = pixel;
    setFloat(pixelLocation, this->pixel);
}