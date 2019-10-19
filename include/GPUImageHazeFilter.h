#ifndef GPU_IMAGE_Haze_FILTER
#define GPU_IMAGE_Haze_FILTER

#include "GPUImageFilter.h" 


class GPUImageHazeFilter : public GPUImageFilter
{
public:
    GPUImageHazeFilter();
    GPUImageHazeFilter(float brightness);
    ~GPUImageHazeFilter();

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