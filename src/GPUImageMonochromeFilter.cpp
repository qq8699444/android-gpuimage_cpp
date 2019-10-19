#include <iostream>

using namespace  std;

#include "GPUImageMonochromeFilter.h"
float GPUImageMonochromeFilter::defaultcolor[3] = { 0.6f, 0.45f, 0.3f };
string GPUImageMonochromeFilter::MONOCHROME_FRAGMENT_SHADER = "" 
        " precision lowp float;\n" 
        "  \n" 
        "  varying highp vec2 textureCoordinate;\n" 
        "  \n" 
        "  uniform sampler2D inputImageTexture;\n" 
        "  uniform float intensity;\n" 
        "  uniform vec3 filterColor;\n" 
        "  \n" 
        "  const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n" 
        "  \n" 
        "  void main()\n" 
        "  {\n" 
        " 	//desat, then apply overlay blend\n" 
        " 	lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
        " 	float luminance = dot(textureColor.rgb, luminanceWeighting);\n" 
        " 	\n" 
        " 	lowp vec4 desat = vec4(vec3(luminance), 1.0);\n" 
        " 	\n" 
        " 	//overlay\n" 
        " 	lowp vec4 outputColor = vec4(\n" 
        "                                  (desat.r < 0.5 ? (2.0 * desat.r * filterColor.r) : (1.0 - 2.0 * (1.0 - desat.r) * (1.0 - filterColor.r))),\n" 
        "                                  (desat.g < 0.5 ? (2.0 * desat.g * filterColor.g) : (1.0 - 2.0 * (1.0 - desat.g) * (1.0 - filterColor.g))),\n" 
        "                                  (desat.b < 0.5 ? (2.0 * desat.b * filterColor.b) : (1.0 - 2.0 * (1.0 - desat.b) * (1.0 - filterColor.b))),\n" 
        "                                  1.0\n" 
        "                                  );\n" 
        " 	\n" 
        " 	//which is better, or are they equal?\n" 
        " 	gl_FragColor = vec4( mix(textureColor.rgb, outputColor.rgb, intensity), textureColor.a);\n" 
        "  }";


GPUImageMonochromeFilter::GPUImageMonochromeFilter(float i/* = 1.0f */, float* c/* = defaultcolor */) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, MONOCHROME_FRAGMENT_SHADER),
    intensity(i),
    color(c)
{

}

void GPUImageMonochromeFilter::onInit() {
    GPUImageFilter::onInit();
    intensityLocation = glGetUniformLocation(getProgram(), "intensity");
    filterColorLocation = glGetUniformLocation(getProgram(), "filterColor");
}

void GPUImageMonochromeFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setIntensity(1.0f);
    setColor(color);
}

 void GPUImageMonochromeFilter::setIntensity(float i) {
    intensity = i;
    setFloat(intensityLocation, intensity);
}

 void GPUImageMonochromeFilter::setColor(float* c) {
    color = c;
    //setColor(this.color[0], this.color[1], this.color[2]);
    setFloatVec3(filterColorLocation, color);
}