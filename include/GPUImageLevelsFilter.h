#ifndef GPU_IMAGE_Levels_FILTER
#define GPU_IMAGE_Levels_FILTER

#include "GPUImageFilter.h" 


class GPUImageLevelsFilter : public GPUImageFilter
{
public:
    GPUImageLevelsFilter();
    GPUImageLevelsFilter(float brightness);
    ~GPUImageLevelsFilter();

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