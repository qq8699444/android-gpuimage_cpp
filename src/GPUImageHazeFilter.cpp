#include <iostream>

using namespace  std;

#include "GPUImageHazeFilter.h"

string GPUImageHazeFilter::HAZE_FRAGMENT_SHADER = "" 
        "varying highp vec2 textureCoordinate;\n" 
        "\n" 
        "uniform sampler2D inputImageTexture;\n" 
        "\n" 
        "uniform lowp float distance;\n" 
        "uniform highp float slope;\n" 
        "\n" 
        "void main()\n" 
        "{\n" 
        "	//todo reconsider precision modifiers	 \n" 
        "	 highp vec4 color = vec4(1.0);//todo reimplement as a parameter\n" 
        "\n" 
        "	 highp float  d = textureCoordinate.y * slope  +  distance; \n" 
        "\n" 
        "	 highp vec4 c = texture2D(inputImageTexture, textureCoordinate) ; // consider using unpremultiply\n" 
        "\n" 
        "	 c = (c - d * color) / (1.0 -d);\n" 
        "\n" 
        "	 gl_FragColor = c; //consider using premultiply(c);\n" 
        "}\n";

GPUImageHazeFilter::GPUImageHazeFilter(float d /* = 0.2f */, float s /* = 0.0f */) :
    GPUImageFilter(NO_FILTER_VERTEX_SHADER, HAZE_FRAGMENT_SHADER),
    distance(d),
    slope(s)
{

}

void GPUImageHazeFilter::onInit() {
    GPUImageFilter::onInit();
    distanceLocation = glGetUniformLocation(getProgram(), "distance");
    slopeLocation = glGetUniformLocation(getProgram(), "slope");
}

void GPUImageHazeFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setDistance(distance);
    setSlope(slope);
}

/**
 * Strength of the color applied. Default 0. Values between -.3 and .3 are best.
 *
 * @param distance -0.3 to 0.3 are best, default 0
 */
void GPUImageHazeFilter::setDistance(float d) {
    distance = d;
    setFloat(distanceLocation, distance);
}

/**
 * Amount of color change. Default 0. Values between -.3 and .3 are best.
 *
 * @param slope -0.3 to 0.3 are best, default 0
 */
void GPUImageHazeFilter::setSlope(float s) {
    slope = slope;
    setFloat(slopeLocation, slope);
}