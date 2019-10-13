#include <iostream>

using namespace  std;
#include "ShaderUtil.h"
#include "GPUImageOpacityFilter.h"


string GPUImageOpacityFilter::OPACITY_FRAGMENT_SHADER = "" 
"  varying highp vec2 textureCoordinate;\n" 
"  \n" 
"  uniform sampler2D inputImageTexture;\n" 
"  uniform lowp float opacity;\n" 
"  \n" 
"  void main()\n" 
"  {\n" 
"      lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
"      \n" 
"      gl_FragColor = vec4(textureColor.rgb, textureColor.a * opacity);\n" 
"  }\n";


GPUImageOpacityFilter::GPUImageOpacityFilter(float opacity):
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, OPACITY_FRAGMENT_SHADER)
{
    this->opacity = opacity;
}


void GPUImageOpacityFilter::onInit()
{
    GPUImageFilter::onInit();
    opacityLocation = glGetUniformLocation(getProgram(), "opacity");
}

void GPUImageOpacityFilter::onInitialized()
{
    GPUImageFilter::onInitialized();
    setOpacity(opacity);
}


void GPUImageOpacityFilter::setOpacity(float opacity)
{
    this->opacity = opacity;
    setFloat(opacityLocation, opacity);
}