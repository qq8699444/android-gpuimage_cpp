#include <iostream>

using namespace  std;
#include "ShaderUtil.h"


#include "GPUImage3x3TextureSamplingFilter.h"

string GPUImage3x3TextureSamplingFilter::THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER =  "" 
                    "attribute vec4 position;\n" 
                    "attribute vec4 inputTextureCoordinate;\n" 
                    "\n" 
                    "uniform highp float texelWidth; \n" 
                    "uniform highp float texelHeight; \n" 
                    "\n" 
                    "varying vec2 textureCoordinate;\n" 
                    "varying vec2 leftTextureCoordinate;\n" 
                    "varying vec2 rightTextureCoordinate;\n" 
                    "\n" 
                    "varying vec2 topTextureCoordinate;\n" 
                    "varying vec2 topLeftTextureCoordinate;\n" 
                    "varying vec2 topRightTextureCoordinate;\n" 
                    "\n" 
                    "varying vec2 bottomTextureCoordinate;\n" 
                    "varying vec2 bottomLeftTextureCoordinate;\n" 
                    "varying vec2 bottomRightTextureCoordinate;\n" 
                    "\n" 
                    "void main()\n" 
                    "{\n" 
                    "    gl_Position = position;\n" 
                    "\n" 
                    "    vec2 widthStep = vec2(texelWidth, 0.0);\n" 
                    "    vec2 heightStep = vec2(0.0, texelHeight);\n" 
                    "    vec2 widthHeightStep = vec2(texelWidth, texelHeight);\n" 
                    "    vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);\n" 
                    "\n" 
                    "    textureCoordinate = inputTextureCoordinate.xy;\n" 
                    "    leftTextureCoordinate = inputTextureCoordinate.xy - widthStep;\n" 
                    "    rightTextureCoordinate = inputTextureCoordinate.xy + widthStep;\n" 
                    "\n" 
                    "    topTextureCoordinate = inputTextureCoordinate.xy - heightStep;\n" 
                    "    topLeftTextureCoordinate = inputTextureCoordinate.xy - widthHeightStep;\n" 
                    "    topRightTextureCoordinate = inputTextureCoordinate.xy + widthNegativeHeightStep;\n" 
                    "\n" 
                    "    bottomTextureCoordinate = inputTextureCoordinate.xy + heightStep;\n" 
                    "    bottomLeftTextureCoordinate = inputTextureCoordinate.xy - widthNegativeHeightStep;\n" 
                    "    bottomRightTextureCoordinate = inputTextureCoordinate.xy + widthHeightStep;\n" 
                    "}";


GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter():
    GPUImage3x3TextureSamplingFilter(NO_FILTER_FRAGMENT_SHADER)
{

}

GPUImage3x3TextureSamplingFilter::GPUImage3x3TextureSamplingFilter(string fragmentShader):
    GPUImageFilter(THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER, fragmentShader),
    texelWidth(0.f),
    texelHeight(0.f)
{

}


GPUImage3x3TextureSamplingFilter::~GPUImage3x3TextureSamplingFilter()
{

}


void GPUImage3x3TextureSamplingFilter::onInit()
{
    GPUImageFilter::onInit();
    uniformTexelWidthLocation = glGetUniformLocation(getProgram(), "texelWidth");
    checkGLError("glGetUniformLocation texelWidth");
    uniformTexelHeightLocation = glGetUniformLocation(getProgram(), "texelHeight");
    checkGLError("glGetUniformLocation texelHeight");
}

void GPUImage3x3TextureSamplingFilter::onInitialized()
{
    GPUImageFilter::onInitialized();
    if (texelWidth != 0) {
        updateTexelValues();
    }
}

void GPUImage3x3TextureSamplingFilter::onOutputSizeChanged(int width, int height)
{
    GPUImageFilter::onOutputSizeChanged(width, height);
    if (!hasOverriddenImageSizeFactor) {
        setLineSize(lineSize);
    }
}

void GPUImage3x3TextureSamplingFilter::setTexelWidth(float texelWidth)
{
    hasOverriddenImageSizeFactor = true;
    this->texelWidth = texelWidth;
    setFloat(uniformTexelWidthLocation, texelWidth);
}
void GPUImage3x3TextureSamplingFilter::setTexelHeight(float texelHeight)
{
    hasOverriddenImageSizeFactor = true;
    this->texelHeight = texelHeight;
    setFloat(uniformTexelHeightLocation, texelHeight);
}

void GPUImage3x3TextureSamplingFilter::updateTexelValues()
{
    setFloat(uniformTexelWidthLocation, texelWidth);
    setFloat(uniformTexelHeightLocation, texelHeight);
}


void GPUImage3x3TextureSamplingFilter::setLineSize(float size)
{
    lineSize = size;
    texelWidth = size / getOutputWidth();
    texelHeight = size / getOutputHeight();
    updateTexelValues();
}