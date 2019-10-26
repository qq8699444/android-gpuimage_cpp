#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace  std;

#include "GPUImageSobelEdgeDetectionFilter.h"
#include "GPUImageGrayscaleFilter.h"
#include "GPUImage3x3TextureSamplingFilter.h"

std::string GPUImageSobelEdgeDetectionFilter::SOBEL_EDGE_DETECTION = "" 
        "precision mediump float;\n" 
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
        "uniform sampler2D inputImageTexture;\n" 
        "\n" 
        "void main()\n" 
        "{\n" 
        "    float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;\n" 
        "    float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;\n" 
        "    float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;\n" 
        "    float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;\n" 
        "    float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;\n" 
        "    float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;\n" 
        "    float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;\n" 
        "    float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;\n" 
        "    float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;\n" 
        "    float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;\n" 
        "\n" 
        "    float mag = length(vec2(h, v));\n" 
        "\n" 
        "    gl_FragColor = vec4(vec3(mag), 1.0);\n" 
        "}";

GPUImageSobelEdgeDetectionFilter::GPUImageSobelEdgeDetectionFilter()
{
    std::shared_ptr<GPUImageFilter> f1(new GPUImageGrayscaleFilter());
    addFilter(f1);

    std::shared_ptr<GPUImageFilter> f2(new GPUImage3x3TextureSamplingFilter(SOBEL_EDGE_DETECTION));
    addFilter(f2);
}


void GPUImageSobelEdgeDetectionFilter::setLineSize(float size)
{
    // TODO
}