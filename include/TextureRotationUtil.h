#ifndef texture_rotation_util
#define texture_rotation_util


enum Rotation
{
    NORMAL, 
    ROTATION_90, 
    ROTATION_180, 
    ROTATION_270
};
class TextureRotationUtil
{
public:
	TextureRotationUtil();
	~TextureRotationUtil();

    static float TEXTURE_NO_ROTATION[];
    static float TEXTURE_ROTATED_90[];
    static float TEXTURE_ROTATED_180[];
    static float TEXTURE_ROTATED_270[];

    static float* getRotation(Rotation rotation, bool flipHorizontal,
        bool flipVertical);
protected:
	
private:
    static float flip(float i) {
        if (i == 0.0f) {
            return 1.0f;
        }
        return 0.0f;
    }
};
#endif
