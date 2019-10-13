

#include "TextureRotationUtil.h"

float TextureRotationUtil::TEXTURE_NO_ROTATION[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
};

float TextureRotationUtil::TEXTURE_ROTATED_90[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
};
float TextureRotationUtil::TEXTURE_ROTATED_180[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
};
float TextureRotationUtil::TEXTURE_ROTATED_270[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
};

TextureRotationUtil::TextureRotationUtil()
{

}


TextureRotationUtil::~TextureRotationUtil()
{

}


float* TextureRotationUtil::getRotation(Rotation rotation, bool flipHorizontal, bool flipVertical)
{
    float* rotatedTex;
    switch (rotation) {
    case ROTATION_90:
        rotatedTex = TEXTURE_ROTATED_90;
        break;
    case ROTATION_180:
        rotatedTex = TEXTURE_ROTATED_180;
        break;
    case ROTATION_270:
        rotatedTex = TEXTURE_ROTATED_270;
        break;
    case NORMAL:
    default:
        rotatedTex = TEXTURE_NO_ROTATION;
        break;
    }
    if (flipHorizontal) {
       // TODO
    }
    if (flipVertical) {
        // TODO    
    }
    return rotatedTex;
}