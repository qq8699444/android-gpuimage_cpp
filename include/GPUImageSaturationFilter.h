#ifndef GPU_IMAGE_Saturation_FILTER
#define GPU_IMAGE_Saturation_FILTER

#include "GPUImageFilter.h" 

class GPUImageSaturationFilter: public GPUImageFilter
{
public:
    GPUImageSaturationFilter();
    GPUImageSaturationFilter(float saturation);
    ~GPUImageSaturationFilter();

    void setSaturation(float saturation);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int saturationLocation;
    float saturation;

    static string SATURATION_FRAGMENT_SHADER;
};
#endif