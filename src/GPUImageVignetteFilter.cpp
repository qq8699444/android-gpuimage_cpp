#include <iostream>

using namespace  std;

#include "GPUImageVignetteFilter.h"

string GPUImageVignetteFilter::VIGNETTING_FRAGMENT_SHADER = "" 
        " uniform sampler2D inputImageTexture;\n" 
        " varying highp vec2 textureCoordinate;\n" 
        " \n" 
        " uniform lowp vec2 vignetteCenter;\n" 
        " uniform lowp vec3 vignetteColor;\n" 
        " uniform highp float vignetteStart;\n" 
        " uniform highp float vignetteEnd;\n" 
        " \n" 
        " void main()\n" 
        " {\n" 
        "     /*\n" 
        "     lowp vec3 rgb = texture2D(inputImageTexture, textureCoordinate).rgb;\n" 
        "     lowp float d = distance(textureCoordinate, vec2(0.5,0.5));\n" 
        "     rgb *= (1.0 - smoothstep(vignetteStart, vignetteEnd, d));\n" 
        "     gl_FragColor = vec4(vec3(rgb),1.0);\n" 
        "      */\n" 
        "     \n" 
        "     lowp vec3 rgb = texture2D(inputImageTexture, textureCoordinate).rgb;\n" 
        "     lowp float d = 1.2*distance(textureCoordinate, vec2(vignetteCenter.x, vignetteCenter.y));\n" 
        "     lowp float percent = smoothstep(vignetteStart, vignetteEnd, d);\n" 
        "     gl_FragColor = vec4(mix(rgb.x, vignetteColor.x, percent), mix(rgb.y, vignetteColor.y, percent), mix(rgb.z, vignetteColor.z, percent), 1.0);\n" 
        " }";


static float deaultvignetteColor[] = { 0.0f, 0.0f, 0.0f };
GPUImageVignetteFilter::GPUImageVignetteFilter():
    GPUImageVignetteFilter(0.5f,0.5f, deaultvignetteColor,0.3f, 0.75f)
{

}

GPUImageVignetteFilter::GPUImageVignetteFilter(float vignetteCenterx, float vignetteCentery, 
            float* vignetteColor, float vignetteStart, float vignetteEnd):
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, VIGNETTING_FRAGMENT_SHADER)    
{
    this->vignetteCenterx = vignetteCenterx;
    this->vignetteCentery = vignetteCentery;
    this->vignetteColor = vignetteColor;
    this->vignetteStart = vignetteStart;
    this->vignetteEnd = vignetteEnd;
}

GPUImageVignetteFilter::~GPUImageVignetteFilter()
{

}


void GPUImageVignetteFilter::onInit() {
    GPUImageFilter::onInit();
    vignetteCenterLocation = glGetUniformLocation(getProgram(), "vignetteCenter");
    vignetteColorLocation = glGetUniformLocation(getProgram(), "vignetteColor");
    vignetteStartLocation = glGetUniformLocation(getProgram(), "vignetteStart");
    vignetteEndLocation = glGetUniformLocation(getProgram(), "vignetteEnd");
}

void GPUImageVignetteFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setVignetteCenter(vignetteCenterx, vignetteCentery);
    setVignetteColor(vignetteColor);
    setVignetteStart(vignetteStart);
    setVignetteEnd(vignetteEnd);
}

void GPUImageVignetteFilter::setVignetteCenter(float x,float y) {
    vignetteCenterx = x; vignetteCentery = y;
    setPoint(vignetteCenterLocation, x, y);
}

void GPUImageVignetteFilter::setVignetteColor(float* vignetteColor) {
    this->vignetteColor = vignetteColor;
    setFloatVec3(vignetteColorLocation, vignetteColor);
}

void GPUImageVignetteFilter::setVignetteStart(float vignetteStart) {
    this->vignetteStart = vignetteStart;
    setFloat(vignetteStartLocation, vignetteStart);
}

void GPUImageVignetteFilter::setVignetteEnd(float vignetteEnd) {
    this->vignetteEnd = vignetteEnd;
    setFloat(vignetteEndLocation,vignetteEnd);
}