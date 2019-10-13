#ifndef GPU_IMAGE_3x3TextureSampling_FILTER
#define GPU_IMAGE_3x3TextureSampling_FILTER

#include "GPUImageFilter.h" 
class GPUImage3x3TextureSamplingFilter:public GPUImageFilter
{
public:
    GPUImage3x3TextureSamplingFilter();
    GPUImage3x3TextureSamplingFilter(string fragmentShader);
    virtual ~GPUImage3x3TextureSamplingFilter();

    void setLineSize(float size);
    void setTexelWidth(float texelWidth);
    void setTexelHeight(float texelHeight);
    virtual void onOutputSizeChanged(int width, int height) override;
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
    

    static string THREE_X_THREE_TEXTURE_SAMPLING_VERTEX_SHADER;

    int uniformTexelWidthLocation;
    int uniformTexelHeightLocation;

    bool hasOverriddenImageSizeFactor = false;
    float texelWidth;
    float texelHeight;
    float lineSize = 1.0f;
private:
    void updateTexelValues();
};
#endif