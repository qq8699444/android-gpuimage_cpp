#ifndef GPU_IMAGE_Gamma_FILTER
#define GPU_IMAGE_Gamma_FILTER

#include "GPUImageFilter.h" 


class GPUImageGammaFilter : public GPUImageFilter
{
public:
    GPUImageGammaFilter();
    GPUImageGammaFilter(float brightness);
    ~GPUImageGammaFilter();

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