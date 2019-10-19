#ifndef GPU_IMAGE_ToneCurve_FILTER
#define GPU_IMAGE_ToneCurve_FILTER

#include "GPUImageFilter.h" 


class GPUImageToneCurveFilter : public GPUImageFilter
{
public:
    GPUImageToneCurveFilter();
    GPUImageToneCurveFilter(float brightness);
    ~GPUImageToneCurveFilter();

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