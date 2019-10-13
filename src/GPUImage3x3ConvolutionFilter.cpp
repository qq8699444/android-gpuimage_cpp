#include <iostream>

using namespace  std;
#include "ShaderUtil.h"


#include "GPUImage3x3ConvolutionFilter.h"

string GPUImage3x3ConvolutionFilter::THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER = "" 
    "precision highp float;\n" 
    "\n" 
    "uniform sampler2D inputImageTexture;\n" 
    "\n" 
    "uniform mediump mat3 convolutionMatrix;\n" 
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
    "    mediump vec4 bottomColor = texture2D(inputImageTexture, bottomTextureCoordinate);\n" 
    "    mediump vec4 bottomLeftColor = texture2D(inputImageTexture, bottomLeftTextureCoordinate);\n" 
    "    mediump vec4 bottomRightColor = texture2D(inputImageTexture, bottomRightTextureCoordinate);\n" 
    "    mediump vec4 centerColor = texture2D(inputImageTexture, textureCoordinate);\n" 
    "    mediump vec4 leftColor = texture2D(inputImageTexture, leftTextureCoordinate);\n" 
    "    mediump vec4 rightColor = texture2D(inputImageTexture, rightTextureCoordinate);\n" 
    "    mediump vec4 topColor = texture2D(inputImageTexture, topTextureCoordinate);\n" 
    "    mediump vec4 topRightColor = texture2D(inputImageTexture, topRightTextureCoordinate);\n" 
    "    mediump vec4 topLeftColor = texture2D(inputImageTexture, topLeftTextureCoordinate);\n" 
    "\n" 
    "    mediump vec4 resultColor = topLeftColor * convolutionMatrix[0][0] + topColor * convolutionMatrix[0][1] + topRightColor * convolutionMatrix[0][2];\n" 
    "    resultColor += leftColor * convolutionMatrix[1][0] + centerColor * convolutionMatrix[1][1] + rightColor * convolutionMatrix[1][2];\n" 
    "    resultColor += bottomLeftColor * convolutionMatrix[2][0] + bottomColor * convolutionMatrix[2][1] + bottomRightColor * convolutionMatrix[2][2];\n" 
    "\n" 
    "    gl_FragColor = resultColor;\n" 
    "}";


static float default_3x3_kernel[] = {
                    0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f
};

GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter():
GPUImage3x3ConvolutionFilter(default_3x3_kernel)
{

}


GPUImage3x3ConvolutionFilter::GPUImage3x3ConvolutionFilter(float* kernel):
    GPUImage3x3TextureSamplingFilter(THREE_X_THREE_TEXTURE_SAMPLING_FRAGMENT_SHADER),
    convolutionKernel(kernel)
{

}


GPUImage3x3ConvolutionFilter::~GPUImage3x3ConvolutionFilter()
{

}


void GPUImage3x3ConvolutionFilter::onInit()
{
    GPUImage3x3TextureSamplingFilter::onInit();
    uniformConvolutionMatrix = glGetUniformLocation(getProgram(), "convolutionMatrix");
    ShaderUtil::checkGlError("glGetUniformLocation 3x3 kernel");
}


void GPUImage3x3ConvolutionFilter::onInitialized()
{
    GPUImage3x3TextureSamplingFilter::onInitialized();
    setConvolutionKernel(convolutionKernel);
}

void GPUImage3x3ConvolutionFilter::setConvolutionKernel(float* kernel)
{
    this->convolutionKernel = kernel;
    setUniformMatrix3f(uniformConvolutionMatrix, this->convolutionKernel);
}