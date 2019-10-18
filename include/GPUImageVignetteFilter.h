#ifndef GPU_IMAGE_Vignette_FILTER
#define GPU_IMAGE_Vignette_FILTER

#include "GPUImageFilter.h" 

class GPUImageVignetteFilter: public GPUImageFilter
{
public:
    GPUImageVignetteFilter();
    GPUImageVignetteFilter(float vignetteCenterx, float vignetteCentery,
            float* vignetteColor, 
            float vignetteStart, 
            float vignetteEnd);
    ~GPUImageVignetteFilter();

    void setVignetteStart(float vignetteStart);
    void setVignetteEnd(float vignetteEnd);
    void setVignetteCenter(float x, float y);
    void setVignetteColor(float* vignetteColor);

protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    int vignetteCenterLocation;
    float vignetteCenterx, vignetteCentery;
    int vignetteColorLocation;
    float* vignetteColor;
    int vignetteStartLocation;
    float vignetteStart;
    int vignetteEndLocation;
    float vignetteEnd;

    static string VIGNETTING_FRAGMENT_SHADER;
};
#endif