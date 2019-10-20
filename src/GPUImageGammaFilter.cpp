#include <iostream>

using namespace  std;

#include "GPUImageGammaFilter.h"


string GPUImageGammaFilter::GAMMA_FRAGMENT_SHADER = "" 
        "varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform sampler2D inputImageTexture;\n" 
        " uniform lowp float gamma;\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "     lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        "     \n" 
        "     gl_FragColor = vec4(pow(textureColor.rgb, vec3(gamma)), textureColor.w);\n" 
        " }";


GPUImageGammaFilter::GPUImageGammaFilter(float g/* = 1.2f */) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, GAMMA_FRAGMENT_SHADER),
    gamma(g)
{

}


void GPUImageGammaFilter::onInit() {
    GPUImageFilter::onInit();
    gammaLocation = glGetUniformLocation(getProgram(), "gamma");
}

void GPUImageGammaFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setGamma(gamma);
}

void GPUImageGammaFilter::setGamma(float g) {
    gamma = gamma;
    setFloat(gammaLocation, gamma);
}
