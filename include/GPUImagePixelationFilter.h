#ifndef GPU_IMAGE_Pixelation_FILTER
#define GPU_IMAGE_Pixelation_FILTER

#include "GPUImageFilter.h" 

class GPUImagePixelationFilter :public GPUImageFilter
{
public:
    GPUImagePixelationFilter();
    ~GPUImagePixelationFilter();
    void setPixel(float pixel);
    virtual void onOutputSizeChanged(int width, int height) override;
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int imageWidthFactorLocation;
    int imageHeightFactorLocation;
    float pixel;
    int pixelLocation;

    static string PIXELATION_FRAGMENT_SHADER;
};

#endif