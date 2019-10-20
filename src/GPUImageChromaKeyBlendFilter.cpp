#include <iostream>

using namespace  std;

#include "GPUImageChromaKeyBlendFilter.h"

string GPUImageChromaKeyBlendFilter::CHROMA_KEY_BLEND_FRAGMENT_SHADER = " precision highp float;\n" 
            " \n" 
            " varying highp vec2 textureCoordinate;\n" 
            " varying highp vec2 textureCoordinate2;\n" 
            "\n" 
            " uniform float thresholdSensitivity;\n" 
            " uniform float smoothing;\n" 
            " uniform vec3 colorToReplace;\n" 
            " uniform sampler2D inputImageTexture;\n" 
            " uniform sampler2D inputImageTexture2;\n" 
            " \n" 
            " void main()\n" 
            " {\n" 
            "     vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n" 
            "     vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);\n" 
            "     \n" 
            "     float maskY = 0.2989 * colorToReplace.r + 0.5866 * colorToReplace.g + 0.1145 * colorToReplace.b;\n" 
            "     float maskCr = 0.7132 * (colorToReplace.r - maskY);\n" 
            "     float maskCb = 0.5647 * (colorToReplace.b - maskY);\n" 
            "     \n" 
            "     float Y = 0.2989 * textureColor.r + 0.5866 * textureColor.g + 0.1145 * textureColor.b;\n" 
            "     float Cr = 0.7132 * (textureColor.r - Y);\n" 
            "     float Cb = 0.5647 * (textureColor.b - Y);\n" 
            "     \n" 
            "     float blendValue = 1.0 - smoothstep(thresholdSensitivity, thresholdSensitivity + smoothing, distance(vec2(Cr, Cb), vec2(maskCr, maskCb)));\n" 
            "     gl_FragColor = mix(textureColor, textureColor2, blendValue);\n" 
            " }";


GPUImageChromaKeyBlendFilter::GPUImageChromaKeyBlendFilter() :
    GPUImageTwoInputFilter(CHROMA_KEY_BLEND_FRAGMENT_SHADER)
{

}

void GPUImageChromaKeyBlendFilter::onInit() {
    GPUImageTwoInputFilter::onInit();
    thresholdSensitivityLocation = glGetUniformLocation(getProgram(), "thresholdSensitivity");
    smoothingLocation = glGetUniformLocation(getProgram(), "smoothing");
    colorToReplaceLocation = glGetUniformLocation(getProgram(), "colorToReplace");
}

void GPUImageChromaKeyBlendFilter::onInitialized() {
    GPUImageTwoInputFilter::onInitialized();
    setSmoothing(smoothing);
    setThresholdSensitivity(thresholdSensitivity);
    setColorToReplace(colorToReplace);
}

/**
 * The degree of smoothing controls how gradually similar colors are replaced in the image
 * The default value is 0.1
 */
void GPUImageChromaKeyBlendFilter::setSmoothing(float _smoothing) {
    smoothing = _smoothing;
    setFloat(smoothingLocation, smoothing);
}

/**
 * The threshold sensitivity controls how similar pixels need to be colored to be replaced
 * The default value is 0.3
 */
void GPUImageChromaKeyBlendFilter::setThresholdSensitivity(float _thresholdSensitivity) {
    thresholdSensitivity = _thresholdSensitivity;
    setFloat(thresholdSensitivityLocation, thresholdSensitivity);
}

/**
 * The color to be replaced is specified using individual red, green, and blue components (normalized to 1.0).
 * The default is green: (0.0, 1.0, 0.0).
 *
 * @param redComponent   Red component of color to be replaced
 * @param greenComponent Green component of color to be replaced
 * @param blueComponent  Blue component of color to be replaced
 */
void GPUImageChromaKeyBlendFilter::setColorToReplace(float _colorToReplace[3]) {
    if (colorToReplace != _colorToReplace)
    {
        memcpy(colorToReplace, _colorToReplace, sizeof(colorToReplace));
    }
    
    setFloatVec3(colorToReplaceLocation, colorToReplace);
}