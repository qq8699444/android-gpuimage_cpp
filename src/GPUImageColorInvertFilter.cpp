#include <iostream>

using namespace  std;

#include "GPUImageColorInvertFilter.h"

string GPUImageColorInvertFilter::COLOR_INVERT_FRAGMENT_SHADER = "" 
"varying highp vec2 textureCoordinate;\n" 
"\n" 
"uniform sampler2D inputImageTexture;\n" 
"\n" 
"void main()\n" 
"{\n" 
"    lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
"    \n" 
"    gl_FragColor = vec4((1.0 - textureColor.rgb), textureColor.w);\n" 
"}";


GPUImageColorInvertFilter::GPUImageColorInvertFilter() :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, COLOR_INVERT_FRAGMENT_SHADER)
{

}