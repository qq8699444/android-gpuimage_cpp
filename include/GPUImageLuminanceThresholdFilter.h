#ifndef GPU_IMAGE_Luminance_Threshold_FILTER
#define GPU_IMAGE_Luminance_Threshold_FILTER

#include "GPUImageFilter.h" 


class GPUImageLuminanceThresholdFilter : public GPUImageFilter
{
public:
    GPUImageLuminanceThresholdFilter(float threshold = 0.5f);
    ~GPUImageLuminanceThresholdFilter() = default;

    void setThreshold(float distance);
protected:
    virtual void onInit() override;
    virtual void onInitialized() override;
private:
    float threshold;
    int uniformThresholdLocation;


    static string LUMINANCE_THRESHOLD_FRAGMENT_SHADER;
};
#endif