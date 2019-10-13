#ifndef GPU_IMAGE_TwoInput_FILTER
#define GPU_IMAGE_TwoInput_FILTER

#include "GPUImageFilter.h" 
#include "TextureRotationUtil.h"


class GPUImageTwoInputFilter: public GPUImageFilter
{
public:
	GPUImageTwoInputFilter(string& fragmentShader);
    GPUImageTwoInputFilter(string& vertexShader, string& fragmentShader);
	virtual ~GPUImageTwoInputFilter();

    void setRotation(Rotation rotation, bool flipHorizontal, bool flipVertical);
    string getBitmap() {
        return bitmap;
    }

    void recycleBitmap() {
        //if (bitmap != null && !bitmap.isRecycled()) {
        //    bitmap.recycle();
        //    bitmap = null;
        //}
    }

    virtual void onDestroy() override;
    virtual void onDrawArraysPre() override;
    void setBitmap(string& bitmap);
protected:
	
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    static string VERTEX_SHADER;

    int filterSecondTextureCoordinateAttribute;
    int filterInputTextureUniform2;
    GLuint filterSourceTexture2;
    float* texture2CoordinatesBuffer;
    string bitmap;
};

#endif