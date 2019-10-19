#ifndef GPU_IMAGE_Hue_FILTER
#define GPU_IMAGE_Hue_FILTER

#include "GPUImageFilter.h" 


class GPUImageHueFilter : public GPUImageFilter
{
public:
    GPUImageHueFilter(int hue = 90);
    ~GPUImageHueFilter();

    void setHue(int h);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int hue;
    int hueLocation;

    static string HUE_FRAGMENT_SHADER;
};
#endif