#ifndef GPU_IMAGE_ColorInvert_FILTER
#define GPU_IMAGE_ColorInvert_FILTER

#include "GPUImageFilter.h" 


class GPUImageColorInvertFilter : public GPUImageFilter
{
public:
    GPUImageColorInvertFilter();
    GPUImageColorInvertFilter(float brightness);
    ~GPUImageColorInvertFilter();

    void setBrightness(float b);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int brightnessLocation;
    float brightness;
    static string BRIGHTNESS_FRAGMENT_SHADER;
};
#endif