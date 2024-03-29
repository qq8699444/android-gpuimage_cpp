#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImageBilateralBlurFilter.h"

string GPUImageBilateralBlurFilter::BILATERAL_VERTEX_SHADER = ""
            "attribute vec4 position;\n"
            "attribute vec4 inputTextureCoordinate;\n"
            "const int GAUSSIAN_SAMPLES = 9;\n"
            "uniform vec2 singleStepOffset;\n"
            "varying vec2 textureCoordinate;\n"
            "varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];\n"
            "void main()\n"
            "{\n"
            "	gl_Position = position;\n"
            "	textureCoordinate = inputTextureCoordinate.xy;\n"
            "	int multiplier = 0;\n"
            "	vec2 blurStep;\n"
            "	for (int i = 0; i < GAUSSIAN_SAMPLES; i++)\n"
            "	{\n"
            "		multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));\n"
            "		blurStep = float(multiplier) * singleStepOffset;\n"
            "		blurCoordinates[i] = inputTextureCoordinate.xy + blurStep;\n"
            "	}\n"
            "}";

string GPUImageBilateralBlurFilter::BILATERAL_FRAGMENT_SHADER = "" 
            "uniform sampler2D inputImageTexture;\n" 
            " const lowp int GAUSSIAN_SAMPLES = 9;\n" 
            " varying highp vec2 textureCoordinate;\n" 
            " varying highp vec2 blurCoordinates[GAUSSIAN_SAMPLES];\n" 
            " uniform mediump float distanceNormalizationFactor;\n" 
            " void main()\n" 
            " {\n" 
            "     lowp vec4 centralColor;\n" 
            "     lowp float gaussianWeightTotal;\n" 
            "     lowp vec4 sum;\n" 
            "     lowp vec4 sampleColor;\n" 
            "     lowp float distanceFromCentralColor;\n" 
            "     lowp float gaussianWeight;\n" 
            "     \n" 
            "     centralColor = texture2D(inputImageTexture, blurCoordinates[4]);\n" 
            "     gaussianWeightTotal = 0.18;\n" 
            "     sum = centralColor * 0.18;\n" 
            "     \n" 
            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[0]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 
            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[1]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 
            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[2]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 
            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[3]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 
            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[5]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 
            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[6]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 

            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[7]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 

            "     sampleColor = texture2D(inputImageTexture, blurCoordinates[8]);\n" 
            "     distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);\n" 
            "     gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);\n" 
            "     gaussianWeightTotal += gaussianWeight;\n" 
            "     sum += sampleColor * gaussianWeight;\n" 
            "     gl_FragColor = sum / gaussianWeightTotal;\n" 
            " }";


GPUImageBilateralBlurFilter::GPUImageBilateralBlurFilter() :
    GPUImageBilateralBlurFilter(8.0f)
{

}


GPUImageBilateralBlurFilter::GPUImageBilateralBlurFilter(float f):
    GPUImageFilter(BILATERAL_VERTEX_SHADER, BILATERAL_FRAGMENT_SHADER),
    distanceNormalizationFactor(f)
{

}


GPUImageBilateralBlurFilter::~GPUImageBilateralBlurFilter()
{

}

void GPUImageBilateralBlurFilter::onInit() {
    GPUImageFilter::onInit();
    disFactorLocation = glGetUniformLocation(getProgram(), "distanceNormalizationFactor");
    singleStepOffsetLocation = glGetUniformLocation(getProgram(), "singleStepOffset");
}

void GPUImageBilateralBlurFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setDistanceNormalizationFactor(distanceNormalizationFactor);
}

void GPUImageBilateralBlurFilter::setDistanceNormalizationFactor(float newValue) {
    distanceNormalizationFactor = newValue;
    setFloat(disFactorLocation, newValue);
}

void GPUImageBilateralBlurFilter::setTexelSize(float w, float h) {
    static float vec2[2];
    vec2[0] = 1.0f / w;
    vec2[1] = 1.0f / h;
    setFloatVec2(singleStepOffsetLocation, vec2);
}

void GPUImageBilateralBlurFilter::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    setTexelSize(width, height);
}