#include <iostream>

using namespace  std;

#include "GPUImageHighlightShadowFilter.h"

string GPUImageHighlightShadowFilter::HIGHLIGHT_SHADOW_FRAGMENT_SHADER = "" 
        " uniform sampler2D inputImageTexture;\n" 
        " varying highp vec2 textureCoordinate;\n" 
        "  \n" 
        " uniform lowp float shadows;\n" 
        " uniform lowp float highlights;\n" 
        " \n" 
        " const mediump vec3 luminanceWeighting = vec3(0.3, 0.3, 0.3);\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        " 	lowp vec4 source = texture2D(inputImageTexture, textureCoordinate);\n" 
        " 	mediump float luminance = dot(source.rgb, luminanceWeighting);\n" 
        " \n" 
        " 	mediump float shadow = clamp((pow(luminance, 1.0/(shadows+1.0)) + (-0.76)*pow(luminance, 2.0/(shadows+1.0))) - luminance, 0.0, 1.0);\n" 
        " 	mediump float highlight = clamp((1.0 - (pow(1.0-luminance, 1.0/(2.0-highlights)) + (-0.8)*pow(1.0-luminance, 2.0/(2.0-highlights)))) - luminance, -1.0, 0.0);\n" 
        " 	lowp vec3 result = vec3(0.0, 0.0, 0.0) + ((luminance + shadow + highlight) - 0.0) * ((source.rgb - vec3(0.0, 0.0, 0.0))/(luminance - 0.0));\n" 
        " \n" 
        " 	gl_FragColor = vec4(result.rgb, source.a);\n" 
        " }";

GPUImageHighlightShadowFilter::GPUImageHighlightShadowFilter(float s /* = 0.0f */, float h /* = 1.0f */) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, HIGHLIGHT_SHADOW_FRAGMENT_SHADER),
    shadows(s),
    highlights(h)
{

}

void GPUImageHighlightShadowFilter::onInit() {
    GPUImageFilter::onInit();
    highlightsLocation = glGetUniformLocation(getProgram(), "highlights");
    shadowsLocation = glGetUniformLocation(getProgram(), "shadows");
}

void GPUImageHighlightShadowFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setHighlights(highlights);
    setShadows(shadows);
}

void GPUImageHighlightShadowFilter::setHighlights(float h) {
    highlights = h;
    setFloat(highlightsLocation, highlights);
}

void GPUImageHighlightShadowFilter::setShadows(float s) {
    shadows = shadows;
    setFloat(shadowsLocation, shadows);
}
