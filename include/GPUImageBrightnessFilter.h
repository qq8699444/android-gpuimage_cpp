#ifndef GPU_IMAGE_Brightness_FILTER
#define GPU_IMAGE_Brightness_FILTER

#include "GPUImageFilter.h" 


class GPUImageBrightnessFilter : public GPUImageFilter
{
public:
    GPUImageBrightnessFilter();
    GPUImageBrightnessFilter(float brightness);
    ~GPUImageBrightnessFilter();

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